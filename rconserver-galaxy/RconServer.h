#pragma once
#pragma comment (lib, "Ws2_32.lib")
#include <WS2tcpip.h>
#include <stdint.h>
#include <vector>
#include <mutex>
#include <thread>
#include <memory>
#include <algorithm>
#include <inttypes.h>
#include "RconClient.h"
#include "Logger.h"

class RconServer
{
public:
	RconServer(uint16_t maxClients);
	~RconServer();
	void start();
	void stop();
	void listen();
	void reportEndgame();

private:
	bool running = false;
    std::mutex mtx;
	std::vector<RconClient*> clients;
	SOCKET listenSocket;

	uint16_t port;
	uint16_t maxClients;
	void onClientDisconnect(RconClient *client);
	void onChatInput(std::string const & msg);

    std::shared_ptr<std::thread> workThread;
};