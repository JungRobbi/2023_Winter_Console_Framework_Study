#pragma once
#include "stdafx.h"
#include <iostream>
#include <memory>
#include <thread>
#include <list>
#include <mutex>
#include <string>

#include "../Global.h"

using namespace std;

class Socket;

class NetworkMGR
{
	recursive_mutex mutex;

public:
	char* SERVERIP;
	shared_ptr<Socket> tcpSocket;

	int id;
	string name;
	bool is_mage;

	bool b_isNet; // ���� ���� ����
	bool b_isLogin; // �α��� �Ϸ� ����
	bool b_isLoginProg; // �α��� ���� ������ ����
private:
	NetworkMGR() = default;
	NetworkMGR(const NetworkMGR&) = delete;
	NetworkMGR& operator=(const NetworkMGR&) = delete;
	NetworkMGR(NetworkMGR&&) = delete;
	NetworkMGR& operator=(NetworkMGR&&) = delete;
	~NetworkMGR() = default;
public:
	static NetworkMGR& GetInstance();
	void Initialize();
	void Update();

	void do_connetion();
	void do_recv();
	void do_send(const char* buf, short buf_size);
	void Process_Packet(char* p_Packet);
};