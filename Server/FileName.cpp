#pragma once
#include <iostream>
#include "../Global.h"
#pragma comment(lib, "../x64/Release/ServerLib.lib")
#include "../ServerLib/ServerLibHeaders.h"

using namespace std;

vector<shared_ptr<thread>> worker_threads;

shared_ptr<Socket> p_listenSocket;
shared_ptr<RemoteClient> remoteClientCandidate;

//IOCP를 준비한다.
Iocp iocp(1); // N_THREAD개의 스레드 사용을 API에 힌트로 준다.

void ProcessClientLeave()
{

}

void CloseServer();
void ProcessAccept();

void Worker_Thread()
{
	try
	{
		while (true) {
			// I/O 완료 이벤트가 있을 때까지 기다립니다.
			IocpEvents readEvents;
			iocp.Wait(readEvents, 100);

			// 받은 이벤트 각각을 처리합니다.
			for (int i = 0; i < readEvents.m_eventCount; ++i)
			{
				auto& readEvent = readEvents.m_events[i];
				auto p_readOverlapped = (EXP_OVER*)readEvent.lpOverlapped;

				if (IO_TYPE::IO_SEND == p_readOverlapped->m_ioType) {
					cout << " Send! - size : " << (int)p_readOverlapped->_buf[0] << endl;
					cout << " Send! - type : " << (int)p_readOverlapped->_buf[1] << endl;
					p_readOverlapped->m_isReadOverlapped = false;
					continue;
				}

				if (readEvent.lpCompletionKey == (ULONG_PTR)p_listenSocket.get()) // 리슨소켓이면
				{
					cout << " Accept! key - " << readEvent.lpCompletionKey << endl;
					ProcessAccept(); // 클라이언트 연결 작업
				}
				else  // TCP 연결 소켓이면
				{
					cout << " Recv! - size : " << (int)p_readOverlapped->_buf[0] << endl;
					cout << " Recv! - type : " << (int)p_readOverlapped->_buf[1] << endl;
					
				}
			}
		}
	}
	catch (Exception& e)
	{
		cout << "Exception! " << e.what() << endl;
	}
}

int main(int argc, char* argv[])
{
	auto& packetQueue = PacketQueue::GetInstance();
	packetQueue.Initialize();


	p_listenSocket = make_shared<Socket>(SocketType::Tcp);
	p_listenSocket->Bind(Endpoint("0.0.0.0", SERVERPORT));
	p_listenSocket->Listen();
	// IOCP에 추가한다.
	iocp.Add(*p_listenSocket, p_listenSocket.get());

	remoteClientCandidate = make_shared<RemoteClient>(SocketType::Tcp);

	string errorText;
	if (!p_listenSocket->AcceptOverlapped(remoteClientCandidate->tcpConnection, errorText)
		&& WSAGetLastError() != ERROR_IO_PENDING)
	{
		throw Exception("Overlapped AcceptEx failed."s);
	}
	p_listenSocket->m_isReadOverlapped = true;

	for (int i{}; i < 1; ++i)
		worker_threads.emplace_back(make_shared<thread>(Worker_Thread));
	int MAX_MonsterTimerDelay = 10000;
	int MonsterTimerDelay = 0;

	for (auto& th : worker_threads) th->join();

	// 서버 종료
	CloseServer();
}

void CloseServer()
{

}
void ProcessAccept()
{
	
}


void Process_Packet()
{
	
}

void Process_Timer_Event()
{

}