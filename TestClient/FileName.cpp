#include <iostream>
#include "NetworkMGR.h"
#include "../Global.h"
int main()
{
	auto& packetQueue = PacketQueue::GetInstance();
	packetQueue.Initialize();

	std::cout << " Hello world!" << endl;

	auto& networkMGR = NetworkMGR::GetInstance();
	networkMGR.Initialize();

	while (true) {
		networkMGR.Update();


	}
}