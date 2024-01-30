#include <iostream>
#include "NetworkMGR.h"
#include "../Global.h"
int main()
{
	auto& packetQueue = PacketQueue::GetInstance();
	packetQueue.Initialize();

	auto& networkMGR = NetworkMGR::GetInstance();
	networkMGR.Initialize();

	string str;
	std::cin >> str;

	CS_CHAT_PACKET packet;
	packet.size = sizeof(CS_CHAT_PACKET);
	packet.type = static_cast<unsigned char>(E_PACKET::E_PACKET_CS_CHAT);
	strcpy(packet.data, str.c_str());
	packetQueue.AddSendPacket(&packet);

	while (true) {
		networkMGR.Update();
	}
}