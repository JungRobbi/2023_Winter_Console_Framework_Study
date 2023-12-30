#pragma once
#include "stdafx.h"

enum E_OBJECT {
	E_CLIENT = 0,
	E_ENEMY = 10000,
	E_TILE = 20000,
	E_WALL = 20100,
	E_ITEM = 20200,
};

class Scene
{
	vector<vector<int>> scene;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Render();
};

