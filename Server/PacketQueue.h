#pragma once
#include <list>
#include <memory>

#include "stdafx.h"

class PacketQueue
{
public:
	std::list<char[MAX_BUFSIZE_SEND]> SendQueue;
	std::list<char[MAX_BUFSIZE_RECV]> RecvQueue;

	short SendQueueIndex;
	short RecvQueueIndex;
private:
	PacketQueue() = default;
	PacketQueue(const PacketQueue&) = delete;
	PacketQueue& operator=(const PacketQueue&) = delete;
	PacketQueue(PacketQueue&&) = delete;
	PacketQueue& operator=(PacketQueue&&) = delete;
	~PacketQueue() = default;
public:
	static PacketQueue& GetInstance();

	void Initialize();

	void AddSendPacket(void* packet);
	void AddRecvPacket(void* packet);

	void PopSendPacket();
	void PopRecvPacket();
};

