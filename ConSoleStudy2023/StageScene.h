#pragma once
#include "Scene.h"
class StageScene :
    public Scene
{
	vector<vector<int>> stage;
public:
	StageScene();
	virtual ~StageScene();

	virtual void Initialize();
	virtual void Update(double elapsedTime);
	virtual void Render();
};

