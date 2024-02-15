#pragma once
#include "Scene.h"
class LobbyScene :
    public Scene
{
    vector<vector<int>> lobby;
	Vec2 dungeonPos;
	Vec2 storePos;
	vector<string> dungeonTitle;
	vector<string> storeTitle;
public:
	LobbyScene();
	virtual ~LobbyScene();

	virtual void Initialize();
	virtual void Update(double elapsedTime);
	virtual void Render();

	virtual void ProcessPacket(char* p_Packet);
};

