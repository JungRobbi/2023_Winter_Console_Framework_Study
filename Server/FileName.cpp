#pragma once
#include <iostream>
#include "../Global.h"
#pragma comment(lib, "../x64/Release/ServerLib.lib")
#include "../ServerLib/ServerLibHeaders.h"

using namespace std;

vector<shared_ptr<thread>> worker_threads;

shared_ptr<Socket> p_listenSocket;
shared_ptr<RemoteClient> remoteClientCandidate;

//IOCP�� �غ��Ѵ�.
Iocp iocp(1); // N_THREAD���� ������ ����� API�� ��Ʈ�� �ش�.

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
			// I/O �Ϸ� �̺�Ʈ�� ���� ������ ��ٸ��ϴ�.
			IocpEvents readEvents;
			iocp.Wait(readEvents, 100);

			// ���� �̺�Ʈ ������ ó���մϴ�.
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

				if (readEvent.lpCompletionKey == (ULONG_PTR)p_listenSocket.get()) // ���������̸�
				{
					cout << " Accept! key - " << readEvent.lpCompletionKey << endl;
					ProcessAccept(); // Ŭ���̾�Ʈ ���� �۾�
				}
				else  // TCP ���� �����̸�
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
	// IOCP�� �߰��Ѵ�.
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

	// ���� ����
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