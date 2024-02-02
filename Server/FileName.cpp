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
Iocp iocp{ 1 }; // N_THREAD���� ������ ����� API�� ��Ʈ�� �ش�.

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

					// ó���� Ŭ���̾�Ʈ �޾ƿ���
					shared_ptr<RemoteClient> remoteClient;
					remoteClient = RemoteClient::remoteClients[(RemoteClient*)readEvent.lpCompletionKey];

					if (remoteClient)
					{
						// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
						remoteClient->tcpConnection.m_isReadOverlapped = false;
						int ec = readEvent.dwNumberOfBytesTransferred;

						if (ec <= 0)
						{
							// ���� ����� 0 �� TCP ������ ������...
							// Ȥ�� ���� �� ���� ������ �� �����̴�...
							ProcessClientLeave();
						}
						else
						{
							// �̹� ���ŵ� �����̴�. ���� �Ϸ�� ���� �׳� ���� ����.
							char* recv_buf = remoteClient->tcpConnection.m_recvOverlapped._buf;
							int recv_buf_Length = ec;

							{ // ��Ŷ ������ �� ó��
								int remain_data = recv_buf_Length + remoteClient->tcpConnection.m_prev_remain;
								unsigned char packet_size = recv_buf[0];
								// ���� �����Ͱ� ��ȿ�� �� (0 ���� ũ��, �ϳ��� ��Ŷ ����� ������ �� �ִ� ���)
								while (remain_data > 0 && packet_size <= remain_data) {
									// ��Ŷ ó��
									Process_Packet(remoteClient, recv_buf);

									// ���� ��Ŷ �̵�, ���� ������ ����
									recv_buf += packet_size;
									remain_data -= packet_size;
								}
								// ���� ������ ����
								remoteClient->tcpConnection.m_prev_remain = remain_data;

								// ���� �����Ͱ� 0�� �ƴ� ���� ������ recv_buf�� �� ������ �����Ѵ�.
								if (remain_data > 0) {
									memcpy(remoteClient->tcpConnection.m_recvOverlapped._buf, recv_buf, remain_data);
								}
							}

							// ���� ���� �غ� �Ѵ�.
							if (remoteClient->tcpConnection.ReceiveOverlapped() != 0
								&& WSAGetLastError() != ERROR_IO_PENDING)
							{
								ProcessClientLeave();
							}
							else
							{
								// I/O�� �ɾ���. �ϷḦ ����ϴ� �� ���·� �ٲ���.
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
	// IOCP�� �߰��Ѵ�.
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

	// ���� ����
	CloseServer();
}

void CloseServer()
{

}

void ProcessAccept()
{
	lock_guard<recursive_mutex> lock_accept(mx_accept);
	p_listenSocket->m_isReadOverlapped = false;
	// �̹� accept�� �Ϸ�Ǿ���. ��������, Win32 AcceptEx ������ ������ ������ �۾��� ����. 
	if (remoteClientCandidate->tcpConnection.UpdateAcceptContext(*p_listenSocket) != 0)
	{
		//���������� �ݾҴ��� �ϸ� ���⼭ �������Ŵ�. �׷��� �������� �Ҵɻ��·� ������.
		p_listenSocket->Close();
	}
	else // �� ó����
	{
		shared_ptr<RemoteClient> remoteClient = remoteClientCandidate;
		// �� TCP ���ϵ� IOCP�� �߰��Ѵ�.
		iocp.Add(remoteClient->tcpConnection, remoteClient.get());

		// overlapped ������ ���� �� �־�� �ϹǷ� ���⼭ I/O ���� ��û�� �ɾ�д�.
		if (remoteClient->tcpConnection.ReceiveOverlapped() != 0
			&& WSAGetLastError() != ERROR_IO_PENDING)
		{
			// ����. ������ ��������. �׸��� �׳� ������.
			remoteClient->tcpConnection.Close();
		}
		else
		{
			// I/O�� �ɾ���. �ϷḦ ����ϴ� �� ���·� �ٲ���.
			remoteClient->tcpConnection.m_isReadOverlapped = true;

			// �� Ŭ���̾�Ʈ�� ��Ͽ� �߰�.
			remoteClient->m_id = reinterpret_cast<unsigned long long>(remoteClient.get());
			RemoteClient::remoteClients.insert({ remoteClient.get(), remoteClient });
			cout << "Client joined. There are " << RemoteClient::remoteClients.size() << " connections.\n";

		}

		// ����ؼ� ���� �ޱ⸦ �ؾ� �ϹǷ� �������ϵ� overlapped I/O�� ����.
		remoteClientCandidate = make_shared<RemoteClient>(SocketType::Tcp);
		string errorText;
		if (!p_listenSocket->AcceptOverlapped(remoteClientCandidate->tcpConnection, errorText)
			&& WSAGetLastError() != ERROR_IO_PENDING)
		{
			// �������� �������� �Ҵ� ���·� ������. 
			p_listenSocket->Close();
		}
		else
		{
			// ���������� ������ ������ ��ٸ��� ���°� �Ǿ���.
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
