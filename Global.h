#pragma once
#include <iostream>
#include <string>

// 소켓 버퍼 크기
const int MAX_BUFSIZE = 1024;
//const int MAX_BUFSIZE_RECV = 256;
//const int MAX_BUFSIZE_SEND = 4096;

const int MAX_CHATSIZE = 30;
const int MAX_PACKETSIZE = 128;

const int SERVERPORT = 9423;



enum class E_PACKET
{
	E_PACKET_NONE = 0,

	E_PACKET_CS_CHAT,
	
	E_PACKET_CS_LOGIN,
	E_PACKET_CS_TO_LOBBY,
	E_PACKET_CS_TO_STAGE1,

	E_PACKET_CS_MOVE,

	E_PACKET_SC_CHAT,

	E_PACKET_SC_GIVE_ID,
	E_PACKET_SC_ADD_PLAYER,
	E_PACKET_SC_ADD_MONSTER,

	E_PACKET_SC_MOVE,

};

#pragma pack (push, 1)

class PACKET_HEAD
{
public:
	unsigned char size;
	unsigned char type;
};

//Chatting
class CS_CHAT_PACKET : public PACKET_HEAD {
public:
	char data[MAX_CHATSIZE];
};

class SC_CHAT_PACKET : public PACKET_HEAD {
public:
	unsigned long long id;
	char data[MAX_CHATSIZE];
};

//Scene join
class CS_LOGIN_PACKET : public PACKET_HEAD {
public:
};

class CS_TO_LOBBY_PACKET : public PACKET_HEAD {
public:
};

class CS_TO_STAGE1_PACKET : public PACKET_HEAD {
public:
};

class SC_GIVE_ID_PACKET : public PACKET_HEAD {
public:
	unsigned long long id;
};

class SC_ADD_PLAYER_PACKET : public PACKET_HEAD {
public:
	unsigned long long id;
	int posX;
	int posY;
};

class SC_ADD_MONSTER_PACKET : public PACKET_HEAD {
public:
	unsigned long long id;
	int posX;
	int posY;
	unsigned int monsterType;
};

//Movement
class CS_MOVE_PACKET : public PACKET_HEAD {
public:
	char dir;
};

class SC_MOVE_PACKET : public PACKET_HEAD {
public:
	unsigned long long id;
	char dir;
};

#pragma pack (pop)