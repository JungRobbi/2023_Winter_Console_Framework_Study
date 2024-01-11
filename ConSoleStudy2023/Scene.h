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

	list<shared_ptr<Object>> createQueue;
	list<unsigned long long> removeQueue;
public:
	static Scene* MainScene;
public:
	Scene();
	~Scene();

	void Initialize();
	void Update(double elapsedTime);
	void Render();

	void AddObject(Vec2 pos, int type, unsigned long long id);
	void AddMonster(Vec2 pos, int type, unsigned long long id);
	void AddSkill(Vec2 pos, int type, double holdingTime, unsigned long long id);
	void AddSkill(Vec2 pos, int type, float animateSpeed, double holdingTime, unsigned long long id);

	void RemoveObject(unsigned long long id);
};

