#pragma once
#include "msg.pb.h"

constexpr auto URL = "ipc://tfwnoflydemongf";

struct IpcState
{
	double speed = 1.;
	bool bpmScaleFix = false;
};

class Ipc
{
public:
	Ipc(void (*handleMessage)(messaging::Msg* msg));
	void start();
	void send(messaging::Msg* msg);
private:
	nng::socket sock;
	void (*handleMessage)(messaging::Msg* msg);
	static void receive(nng::socket* sock, void(*handleMessage)(messaging::Msg* msg));
};
