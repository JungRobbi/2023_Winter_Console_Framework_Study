#pragma once
#include <iostream>
#include <string>

// 소켓 버퍼 크기
const int MAX_BUFSIZE = 1024;
//const int MAX_BUFSIZE_RECV = 256;
//const int MAX_BUFSIZE_SEND = 4096;

const int MAX_CHATSIZE = 30;

const int SERVERPORT = 9423;

enum class E_PACKET
{
	E_PACKET_NONE = 0,

	E_PACKET_CS_CHAT,
	E_PACKET_SC_CHAT,
};

#pragma pack (push, 1)

class PACKET_HEAD
{
public:
	unsigned char size;
	unsigned char type;
};

class CS_CHAT_PACKET : public PACKET_HEAD {
public:
	char data[MAX_CHATSIZE];
};

class SC_CHAT_PACKET : public PACKET_HEAD {
public:
	unsigned long long id;
	char data[MAX_CHATSIZE];
};

#pragma pack (pop)