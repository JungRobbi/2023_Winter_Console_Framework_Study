#pragma once
#include "stdafx.h"
#include "Object.h"

class Scene
{
	vector<vector<int>> stage;
	vector<vector<int>> scene;
	unordered_map<unsigned long long, shared_ptr<Object>> objects;
	unsigned long long my_id = 0;

	unordered_map<int, string> Object_Shapes{};
	unordered_map<int, vector<int>> Object_Animation{};


	static unsigned long long global_id;
	static unsigned long long global_effect_id;
public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Render();
};

