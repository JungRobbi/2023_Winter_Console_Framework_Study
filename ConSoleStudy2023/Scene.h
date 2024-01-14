#pragma once
#include "stdafx.h"
#include "Object.h"

class Scene
{
	vector<vector<int>> stage;
	vector<vector<int>> scene;
	unordered_map<unsigned long long, shared_ptr<Object>> objects;

	unordered_map<int, string> Object_Shapes{};
	unordered_map<int, vector<int>> Object_Animation{};

	static unsigned long long global_id;
	static unsigned long long global_effect_id;

	list<shared_ptr<Object>> createQueue;
	list<unsigned long long> removeQueue;

	unsigned long long my_id = 0;
public:
	static Scene* MainScene;
public:
	Scene();
	~Scene();

	void Initialize();
	void Update(double elapsedTime);
	void Render();

	void AddObject(Vec2 pos, int type);
	void AddMonster(Vec2 pos, int type);
	void AddSkill(Vec2 pos, int type, double holdingTime);
	void AddSkill(Vec2 pos, int type, float animateSpeed, double holdingTime);

	void RemoveObject(unsigned long long id);

	vector<unsigned long long> CollideCheck(Vec2 position);
};

