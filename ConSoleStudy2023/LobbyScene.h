#pragma once
#include "Scene.h"
class LobbyScene :
    public Scene
{
    vector<vector<int>> lobby;
public:
	LobbyScene();
	virtual ~LobbyScene();

	virtual void Initialize();
	virtual void Update(double elapsedTime);
	virtual void Render();
};

