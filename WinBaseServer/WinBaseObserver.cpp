#include "WinBaseObserver.h"

#include <thread>
#include <iostream>

class WinBaseObserver::ServerObserverPrivate {
public:
	ServerObserverPrivate()
		:isConnected(true)
		, clientAddr("")
		, heartBuff("heart") {
	}
public:
	SOCKET sockConnect;
	bool isConnected;//是否保持连接
	std::string clientAddr;//客户端地址
	std::string heartBuff;//心跳信息
};

WinBaseObserver::WinBaseObserver(const SOCKET &sockConnect, const std::string &clientAddr)
	:_p(new ServerObserverPrivate())
{
	_p->sockConnect = sockConnect;
	_p->clientAddr = clientAddr;
}

WinBaseObserver::~WinBaseObserver()
{
	delete _p;
}

void WinBaseObserver::HeartBeat() {
	while (_p->isConnected) {
		Sleep(300);
		if (SOCKET_ERROR == _p->sockConnect || SOCKET_ERROR == send(_p->sockConnect, _p->heartBuff.c_str(), sizeof(_p->heartBuff), 0)) {
			_p->isConnected = false;
			break;
		}
	}
}

void WinBaseObserver::Run() {
	std::cout << "建立与" << _p->clientAddr << "的连接!" << std::endl;

	std::thread *heartthread = new std::thread(&WinBaseObserver::HeartBeat, this);
	heartthread->detach();

	std::thread *receiveThread = new std::thread(&WinBaseObserver::ReceiveMessage, this);
	receiveThread->detach();

	while (_p->isConnected) {

	}

	delete heartthread;

	delete receiveThread;

	std::cout << "断开与" << _p->clientAddr << "的连接!" << std::endl;
	closesocket(_p->sockConnect);
}

void WinBaseObserver::ReceiveMessage() {
	while (_p->isConnected) {
		char recvBuf[1024];
		memset(recvBuf, 0, sizeof(recvBuf));
		int rec = recv(_p->sockConnect, recvBuf, sizeof(recvBuf), 0);
		if (rec == 0 || rec == -1) {
			_p->isConnected = false;
			break;
		}
		if (recvBuf == _p->heartBuff) continue;
		std::cout << "收到来自" << _p->clientAddr << "的消息：" << recvBuf << std::endl << "开始处理该消息..." << std::endl;

		OnCommingMessage(recvBuf);

		std::cout << "处理完毕!" << std::endl;
	}
}

void WinBaseObserver::OnCommingMessage(const std::string &message) {
}

void WinBaseObserver::startObserver() {
	Run();
}

void WinBaseObserver::SendMessageToClient(const std::string &message) {
	send(_p->sockConnect, message.c_str(), message.length(), 0);
}
