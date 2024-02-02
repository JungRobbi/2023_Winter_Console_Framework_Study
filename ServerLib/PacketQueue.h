#pragma once
#include "stdafx.h"
#include <list>
#include <memory>

#include "../Global.h"

class PacketQueue
{
public:
	std::list<char[MAX_BUFSIZE]> SendQueue;
	std::list<char[MAX_PACKETSIZE]> RecvQueue;

	short SendQueueIndex;
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

