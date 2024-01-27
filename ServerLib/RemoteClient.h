#pragma once
#include <thread>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <concurrent_unordered_map.h>
#include <atomic>
#include "Socket.h"

using namespace std;
using namespace concurrency;

class RemoteClient {
public:
	static concurrent_unordered_map<RemoteClient*, shared_ptr<RemoteClient>> remoteClients;
public:
	shared_ptr<thread> thread;	// 클라이언트 스레드
	Socket tcpConnection;		// accept한 TCP 연결

	unsigned long long m_id;

	RemoteClient() : thread(), tcpConnection(SocketType::Tcp), m_id() {}
	RemoteClient(SocketType socketType) :tcpConnection(socketType) {}
};