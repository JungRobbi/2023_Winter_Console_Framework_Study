#include "PacketQueue.h"

PacketQueue& PacketQueue::GetInstance()
{
	static PacketQueue instance;
	return instance;
}

void PacketQueue::Initialize()
{
	SendQueue = std::list<char[MAX_BUFSIZE]>{};
	RecvQueue = std::list<char[MAX_BUFSIZE]>{};
	SendQueueIndex = 0;
	RecvQueueIndex = 0;
}

void PacketQueue::AddSendPacket(void* packet)
{
	char* p = reinterpret_cast<char*>(packet);

	if (SendQueue.empty())
		SendQueue.emplace_back();

	//�̹� �ִ� Send ���۰� �߰��Ϸ��� ��Ŷ�� ���� �� �ִٸ�
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

}

void PacketQueue::PopSendPacket()
{
	SendQueueIndex = 0;
	SendQueue.pop_front();
}

void PacketQueue::PopRecvPacket()
{
	RecvQueueIndex = 0;
	RecvQueue.pop_front();
}
