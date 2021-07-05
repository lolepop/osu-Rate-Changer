#include "stdafx.h"

std::mutex mtx;

Ipc::Ipc(void (*handleMessage)(messaging::Msg* msg))
{
	this->handleMessage = handleMessage;

	this->sock = nng::pair::v0::open();
	this->sock.dial(URL);
	
	std::cout << "\nconnected\n";
}

void Ipc::start()
{
	std::thread(Ipc::receive, &this->sock, this->handleMessage).detach();

	messaging::Msg connectedMsg;
	connectedMsg.set_dllmsg(messaging::DllMsg::CONNECTED);
	this->send(&connectedMsg);
}

void Ipc::send(messaging::Msg* m)
{
	auto str = m->SerializeAsString();
	auto msg = nng::make_msg(0);
	msg.body().append({ str.c_str(), str.length() });

	mtx.lock();
	this->sock.send(std::move(msg));
	mtx.unlock();
}

void Ipc::receive(nng::socket* sock, void (*handleMessage)(messaging::Msg* msg))
{
	while (true)
	{
		mtx.lock();

		nng::msg msg;
		bool flag = false;
		try
		{
			msg = sock->recv_msg(NNG_FLAG_NONBLOCK);
		}
		catch (const std::exception& e)
		{
			flag = true;
		}
		mtx.unlock();

		if (!flag)
		{
			auto msgbody = msg.body().get();
			messaging::Msg res;
			res.ParseFromArray(msgbody.data(), msgbody.size());

			handleMessage(&res);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
