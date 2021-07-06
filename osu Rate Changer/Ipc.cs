using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using nng;
using Messaging;
using Google.Protobuf;
using System.Reactive;
using System.Reactive.Linq;
using System.Reactive.Concurrency;
using System.Reactive.Subjects;

namespace osu_Rate_Changer
{
    public class IpcHandler : IDisposable
    {
        public Ipc Connection { get; private set; }
        private Task InboundThread { get; set; }
        public BehaviorSubject<bool> IsReadyToSend { get; private set; } = new(false);

        private IDisposable InboundMessageSubscription { get; set; }
        private Subject<Messaging.Msg> OutboundMessageStream { get; set; } = new();

        public delegate void HandleResponseMessage(Messaging.Msg msg);
        public event HandleResponseMessage ResponseMessage;

        private readonly object obj = new object();

        public IpcHandler()
        {
            Connection = new Ipc();
            StartInboundThread();
        }

        private void StartInboundThread()
        {
            InboundMessageSubscription = Observable.Interval(TimeSpan.FromMilliseconds(10))
                .Select(_ => Connection.Receive())
                .Where(msg => msg != null)
                .Subscribe(HandleMessage);

            OutboundMessageStream
                .Where(_ => IsReadyToSend.Value)
                .Subscribe(Connection.Send);
        }

        private void HandleMessage(Messaging.Msg msg)
        {
            lock (obj)
            {
                switch (msg?.DllMsg)
                {
                    case DllMsg.Connected:
                        IsReadyToSend.OnNext(true);
                        IsReadyToSend.OnCompleted();
                        break;
                    case DllMsg.Response:
                        ResponseMessage?.Invoke(msg);
                        break;
                    default:
                        break;
                }
            }
        }

        public void Send(Messaging.Msg msg) => OutboundMessageStream.OnNext(msg);

        public void Dispose()
        {
            Connection?.Dispose();
            InboundThread?.Dispose();
            InboundMessageSubscription?.Dispose();
            OutboundMessageStream?.Dispose();
            IsReadyToSend?.Dispose();
        }
    }

    public class Ipc : IDisposable
    {
        public IAPIFactory<INngMsg> Factory { get; private set; }
        public IPairSocket Socket { get; private set; }

        public readonly string URL = "ipc://tfwnoflydemongf";

        public ISendReceiveAsyncContext<INngMsg> Ctx { get; set; }

        public Ipc()
        {
            var path = Path.GetDirectoryName(typeof(Program).Assembly.Location);
            var ctx = new nng.NngLoadContext(path);
            Factory = nng.NngLoadContext.Init(ctx);

            Socket = Factory.PairOpen().ThenListenAs(out var _, URL).Unwrap();
            Ctx = Socket.CreateAsyncContext(Factory).Unwrap();
        }

        // how do i timeout the async send theres no cancellation token lmao
        public void Send(Messaging.Msg message)
        {
            Socket.Send(message.ToByteArray(), nng.Native.Defines.NngFlag.NNG_FLAG_NONBLOCK);
            //await Ctx.Send(msg);
        }

        //poll sync to avoid deadlocking thread when awaiting receive and trying to send at same time
        public Messaging.Msg Receive()
        {
            var received = Socket.RecvMsg(nng.Native.Defines.NngFlag.NNG_FLAG_NONBLOCK);
            if (received.IsErr())
                return null;
            //var received = await Ctx.Receive((new CancellationTokenSource()).Token);
            return Messaging.Msg.Parser.ParseFrom(received.Unwrap().AsSpan());
        }

        public void Dispose()
        {
            Socket?.Dispose();
        }
    }

}
