#include <algorithm>
#include <string>
#include "NetworkMGR.h"
#include "../ServerLib/ServerLibHeaders.h"
#include "Scene.h"

#pragma comment(lib, "../x64/Release/ServerLib.lib")
#pragma comment(lib, "WS2_32.LIB")

void CALLBACK recv_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED recv_over, DWORD recv_flag)
{
	char* recv_buf = reinterpret_cast<EXP_OVER*>(recv_over)->_buf;
	int recv_buf_Length = num_bytes;
	auto& netWorkMGR = NetworkMGR::GetInstance();

	{ // 패킷 수신
		int remain_data = recv_buf_Length + netWorkMGR.tcpSocket->m_prev_remain;
		unsigned char packet_size = recv_buf[0];
		while (remain_data > 0 && packet_size <= remain_data) {
			if (packet_size == 0) {
				remain_data = 0;
				break;
			}

			// 패킷 처리
			netWorkMGR.Process_Packet(recv_buf);

			cout << " RECV!" << endl;

			// 다음 패킷 이동, 남은 데이터 갱신
			recv_buf += packet_size;
			remain_data -= packet_size;
		}
		// 남은 데이터 저장
		netWorkMGR.tcpSocket->m_prev_remain = remain_data;

		// 남은 데이터가 0이 아닌 값을 가지면 recv_buf의 맨 앞으로 복사한다.
		if (remain_data > 0) {
			memcpy(netWorkMGR.tcpSocket->m_recvOverlapped._buf, recv_buf, remain_data);
		}
	}

	memset(netWorkMGR.tcpSocket->m_recvOverlapped._buf + netWorkMGR.tcpSocket->m_prev_remain, 0,
		sizeof(netWorkMGR.tcpSocket->m_recvOverlapped._buf) - netWorkMGR.tcpSocket->m_prev_remain);
	memset(&netWorkMGR.tcpSocket->m_recvOverlapped._wsa_over, 0, sizeof(netWorkMGR.tcpSocket->m_recvOverlapped._wsa_over));
	netWorkMGR.do_recv();
}

void CALLBACK send_callback(DWORD err, DWORD num_bytes, LPWSAOVERLAPPED send_over, DWORD recv_flag)
{
	delete reinterpret_cast<EXP_OVER*>(send_over);
}

NetworkMGR& NetworkMGR::GetInstance()
{
	static NetworkMGR instance;
	return instance;
}

void NetworkMGR::Initialize()
{
	tcpSocket = make_shared<Socket>(SocketType::Tcp);

	char isnet = 'n';
	std::cout << "서버 연결 여부(y) : ";
	std::cin >> isnet;

	system("cls");

	if (isnet != 'y') {
		b_isNet = false;
		b_isLogin = true;
		return;
	}
	b_isNet = true;

	std::cout << std::endl << " ======== Login ======== " << std::endl << std::endl;

	std::cout << std::endl << "서버 주소 입력(ex 197.xxx.xxx.xxx) : " << std::endl;
	std::string server_s;
	std::cin >> server_s;
	SERVERIP = new char[server_s.size() + 1];
	SERVERIP[server_s.size()] = '\0';
	strcpy(SERVERIP, server_s.c_str());

	system("cls");

	tcpSocket->Bind(Endpoint::Any);
	NetworkMGR::do_connetion();
	NetworkMGR::do_recv();
}

void NetworkMGR::Update()
{
	SleepEx(0, true);
	auto& packetQueue = PacketQueue::GetInstance();
	if (packetQueue.SendQueue.empty() || tcpSocket->m_fd == INVALID_SOCKET)
		return;

	while (!packetQueue.SendQueue.empty()) {
		char* send_buf = packetQueue.SendQueue.front();

		int buf_size{};
		while (true) {
			if (buf_size + send_buf[buf_size] > MAX_BUFSIZE || send_buf[buf_size] == 0)
				break;
			buf_size += send_buf[buf_size];
		}

		do_send(send_buf, buf_size);
		packetQueue.PopSendPacket();
	}
}

void NetworkMGR::do_connetion() {
	tcpSocket->Connect(Endpoint(SERVERIP, SERVERPORT));
}

void NetworkMGR::do_recv() {
	tcpSocket->m_readFlags = 0;
	ZeroMemory(&tcpSocket->m_recvOverlapped._wsa_over, sizeof(tcpSocket->m_recvOverlapped._wsa_over));
	tcpSocket->m_recvOverlapped._wsa_buf.len = MAX_BUFSIZE - tcpSocket->m_prev_remain;
	tcpSocket->m_recvOverlapped._wsa_buf.buf = tcpSocket->m_recvOverlapped._buf + tcpSocket->m_prev_remain;

	WSARecv(tcpSocket->m_fd, &(tcpSocket->m_recvOverlapped._wsa_buf), 1, 0, &tcpSocket->m_readFlags, &(tcpSocket->m_recvOverlapped._wsa_over), recv_callback);
}

void NetworkMGR::do_send(const char* buf, short buf_size) {
	EXP_OVER* send_over = new EXP_OVER(buf, buf_size);
	WSASend(tcpSocket->m_fd, &send_over->_wsa_buf, 1, 0, 0, &send_over->_wsa_over, send_callback);
}

void NetworkMGR::Process_Packet(char* p_Packet)
{
	E_PACKET type = static_cast<E_PACKET>(p_Packet[1]);
	auto& packetQueue = PacketQueue::GetInstance();

	switch (type)
	{
	case E_PACKET::E_PACKET_NONE:
		break;
	case E_PACKET::E_PACKET_SC_CHAT: 
	{
		SC_CHAT_PACKET* recvPacket = reinterpret_cast<SC_CHAT_PACKET*>(p_Packet);

		cout << recvPacket->id << " CHAT : " << recvPacket->data << endl;
		break; 
	}
	case E_PACKET::E_PACKET_SC_GIVE_ID:
	{
		SC_GIVE_ID_PACKET* recvPacket = reinterpret_cast<SC_GIVE_ID_PACKET*>(p_Packet);

		id = Scene::my_id = recvPacket->id;
		cout << "GIVED ID! " << id << endl;
		break;
	}
	case E_PACKET::E_PACKET_SC_ADD_PLAYER:
	case E_PACKET::E_PACKET_SC_ADD_MONSTER:
	case E_PACKET::E_PACKET_SC_MOVE:
		packetQueue.AddRecvPacket(p_Packet);
		break;
	}
}
