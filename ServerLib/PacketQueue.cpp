#include "PacketQueue.h"

PacketQueue& PacketQueue::GetInstance()
{
	static PacketQueue instance;
	return instance;
}

void PacketQueue::Initialize()
{
	SendQueue = std::list<char[MAX_BUFSIZE]>{};
	RecvQueue = std::list<char[MAX_PACKETSIZE]>{};
	SendQueueIndex = 0;
}

void PacketQueue::AddSendPacket(void* packet)
{
	char* p = reinterpret_cast<char*>(packet);

	if (SendQueue.empty())
		SendQueue.emplace_back();

	//이미 있는 Send 버퍼가 추가하려는 패킷을 담을 수 있다면
	if (SendQueueIndex + p[0] < MAX_BUFSIZE) {
		memcpy(SendQueue.back() + SendQueueIndex, p, p[0]);
		SendQueueIndex += p[0];
	}
	else {
		SendQueueIndex = 0;
		SendQueue.emplace_back();
		memcpy(SendQueue.back() + SendQueueIndex, p, p[0]);
	}
}

void PacketQueue::AddRecvPacket(void* packet)
{
	char* p = reinterpret_cast<char*>(packet);
	
	RecvQueue.emplace_back();
	memcpy(RecvQueue.back(), p, p[0]);
}

void PacketQueue::PopSendPacket()
{
	SendQueueIndex = 0;
	SendQueue.pop_front();
}

void PacketQueue::PopRecvPacket()
{
	RecvQueue.pop_front();
}
