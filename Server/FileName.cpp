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
Iocp iocp{ 1 }; // N_THREAD개의 스레드 사용을 API에 힌트로 준다.

recursive_mutex mx_accept;

void ProcessClientLeave()
{

}

void CloseServer();
void ProcessAccept();
void Process_Packet(shared_ptr<RemoteClient>& p_Client, char* p_Packet);

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

					// 처리할 클라이언트 받아오기
					shared_ptr<RemoteClient> remoteClient;
					remoteClient = RemoteClient::remoteClients[(RemoteClient*)readEvent.lpCompletionKey];

					if (remoteClient)
					{
						// 이미 수신된 상태이다. 수신 완료된 것을 그냥 꺼내 쓰자.
						remoteClient->tcpConnection.m_isReadOverlapped = false;
						int ec = readEvent.dwNumberOfBytesTransferred;

						if (ec <= 0)
						{
							// 읽은 결과가 0 즉 TCP 연결이 끝났다...
							// 혹은 음수 즉 뭔가 에러가 난 상태이다...
							ProcessClientLeave();
						}
						else
						{
							// 이미 수신된 상태이다. 수신 완료된 것을 그냥 꺼내 쓰자.
							char* recv_buf = remoteClient->tcpConnection.m_recvOverlapped._buf;
							int recv_buf_Length = ec;

							{ // 패킷 재조립 및 처리
								int remain_data = recv_buf_Length + remoteClient->tcpConnection.m_prev_remain;
								unsigned char packet_size = recv_buf[0];
								// 남은 데이터가 유효할 때 (0 보다 크고, 하나의 패킷 사이즈를 포함할 수 있는 경우)
								while (remain_data > 0 && packet_size <= remain_data) {
									// 패킷 처리
									Process_Packet(remoteClient, recv_buf);

									// 다음 패킷 이동, 남은 데이터 갱신
									recv_buf += packet_size;
									remain_data -= packet_size;
								}
								// 남은 데이터 저장
								remoteClient->tcpConnection.m_prev_remain = remain_data;

								// 남은 데이터가 0이 아닌 값을 가지면 recv_buf의 맨 앞으로 복사한다.
								if (remain_data > 0) {
									memcpy(remoteClient->tcpConnection.m_recvOverlapped._buf, recv_buf, remain_data);
								}
							}

							// 수신 받을 준비를 한다.
							if (remoteClient->tcpConnection.ReceiveOverlapped() != 0
								&& WSAGetLastError() != ERROR_IO_PENDING)
							{
								ProcessClientLeave();
							}
							else
							{
								// I/O를 걸었다. 완료를 대기하는 중 상태로 바꾸자.
								remoteClient->tcpConnection.m_isReadOverlapped = true;
							}
						}
					}
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
		&& WSAGetLastError() != ERROR_IO_PENDING) {
		throw Exception("Overlapped AcceptEx failed."s);
	}
	p_listenSocket->m_isReadOverlapped = true;

	for (int i{}; i < 1; ++i)
		worker_threads.emplace_back(make_shared<thread>(Worker_Thread));

	for (auto& th : worker_threads) th->join();

	// 서버 종료
	CloseServer();
}

void CloseServer()
{

}

void ProcessAccept()
{
	lock_guard<recursive_mutex> lock_accept(mx_accept);
	p_listenSocket->m_isReadOverlapped = false;
	// 이미 accept은 완료되었다. 귀찮지만, Win32 AcceptEx 사용법에 따르는 마무리 작업을 하자. 
	if (remoteClientCandidate->tcpConnection.UpdateAcceptContext(*p_listenSocket) != 0)
	{
		//리슨소켓을 닫았던지 하면 여기서 에러날거다. 그러면 리슨소켓 불능상태로 만들자.
		p_listenSocket->Close();
	}
	else // 잘 처리함
	{
		shared_ptr<RemoteClient> remoteClient = remoteClientCandidate;
		// 새 TCP 소켓도 IOCP에 추가한다.
		iocp.Add(remoteClient->tcpConnection, remoteClient.get());

		// overlapped 수신을 받을 수 있어야 하므로 여기서 I/O 수신 요청을 걸어둔다.
		if (remoteClient->tcpConnection.ReceiveOverlapped() != 0
			&& WSAGetLastError() != ERROR_IO_PENDING)
		{
			// 에러. 소켓을 정리하자. 그리고 그냥 버리자.
			remoteClient->tcpConnection.Close();
		}
		else
		{
			// I/O를 걸었다. 완료를 대기하는 중 상태로 바꾸자.
			remoteClient->tcpConnection.m_isReadOverlapped = true;

			// 새 클라이언트를 목록에 추가.
			remoteClient->m_id = reinterpret_cast<unsigned long long>(remoteClient.get());
			RemoteClient::remoteClients.insert({ remoteClient.get(), remoteClient });
			cout << "Client joined. There are " << RemoteClient::remoteClients.size() << " connections.\n";

		}

		// 계속해서 소켓 받기를 해야 하므로 리슨소켓도 overlapped I/O를 걸자.
		remoteClientCandidate = make_shared<RemoteClient>(SocketType::Tcp);
		string errorText;
		if (!p_listenSocket->AcceptOverlapped(remoteClientCandidate->tcpConnection, errorText)
			&& WSAGetLastError() != ERROR_IO_PENDING)
		{
			// 에러나면 리슨소켓 불능 상태로 남기자. 
			p_listenSocket->Close();
		}
		else
		{
			// 리슨소켓은 연결이 들어옴을 기다리는 상태가 되었다.
			p_listenSocket->m_isReadOverlapped = true;
		}
	}
}

void Process_Packet(shared_ptr<RemoteClient>& p_Client, char* p_Packet)
{
	auto& packetQueue = PacketQueue::GetInstance();
	E_PACKET type = static_cast<E_PACKET>(p_Packet[1]);

	switch (type)
	{
	case E_PACKET::E_PACKET_NONE:
		break;
	case E_PACKET::E_PACKET_CS_CHAT: 
	{
		CS_CHAT_PACKET* recvPacket = reinterpret_cast<CS_CHAT_PACKET*>(p_Packet);

		SC_CHAT_PACKET sendPacket;
		sendPacket.size = sizeof(SC_CHAT_PACKET);
		sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_SC_CHAT);
		sendPacket.id = p_Client->m_id;
		strcpy(sendPacket.data, recvPacket->data);
		p_Client->tcpConnection.SendOverlapped(reinterpret_cast<char*>(&sendPacket));
		break;
	}
	case E_PACKET::E_PACKET_CS_LOGIN: 
	{
		CS_LOGIN_PACKET* recvPacket = reinterpret_cast<CS_LOGIN_PACKET*>(p_Packet);

		SC_GIVE_ID_PACKET sendPacket;
		sendPacket.size = sizeof(SC_GIVE_ID_PACKET);
		sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_SC_GIVE_ID);
		sendPacket.id = p_Client->m_id;
		p_Client->tcpConnection.SendOverlapped(reinterpret_cast<char*>(&sendPacket));
		break;
	}
	case E_PACKET::E_PACKET_CS_TO_LOBBY: 
	{
		CS_TO_LOBBY_PACKET* recvPacket = reinterpret_cast<CS_TO_LOBBY_PACKET*>(p_Packet);

		SC_ADD_PLAYER_PACKET sendPacket;
		sendPacket.size = sizeof(SC_ADD_PLAYER_PACKET);
		sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_SC_ADD_PLAYER);
		sendPacket.id = p_Client->m_id;
		p_Client->tcpConnection.SendOverlapped(reinterpret_cast<char*>(&sendPacket));
		break;
	}
	case E_PACKET::E_PACKET_CS_TO_STAGE1: 
	{
		CS_TO_STAGE1_PACKET* recvPacket = reinterpret_cast<CS_TO_STAGE1_PACKET*>(p_Packet);

		SC_ADD_MONSTER_PACKET sendPacket;
		sendPacket.size = sizeof(SC_ADD_MONSTER_PACKET);
		sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_SC_ADD_MONSTER);
		sendPacket.id = p_Client->m_id;
		p_Client->tcpConnection.SendOverlapped(reinterpret_cast<char*>(&sendPacket));
		break;
	}
	case E_PACKET::E_PACKET_CS_MOVE: 
	{
		CS_MOVE_PACKET* recvPacket = reinterpret_cast<CS_MOVE_PACKET*>(p_Packet);

		SC_MOVE_PACKET sendPacket;
		sendPacket.size = sizeof(SC_MOVE_PACKET);
		sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_CS_MOVE);
		sendPacket.id = p_Client->m_id;
		sendPacket.dir = recvPacket->dir;
		p_Client->tcpConnection.SendOverlapped(reinterpret_cast<char*>(&sendPacket));
		break;
	}
	}

}
