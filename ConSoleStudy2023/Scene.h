#pragma once
#include "stdafx.h"
#include "Object.h"

enum E_OBJECT {
	E_CLIENT = 0,
	E_ENEMY = 10000,
	E_TILE = 20000,
	E_WALL = 20100,
	E_ITEM = 20200,
};

class Scene
{
	vector<vector<int>> stage;
	vector<vector<int>> scene;
	unordered_map<unsigned long long, shared_ptr<Object>> objects;

	unsigned long long my_id = 0;

	static unsigned long long global_id;
public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Render();
};

