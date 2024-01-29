#pragma once
#include "stdafx.h"
#include "Object.h"
#include "AnimationMGR.h"

enum class E_SCENE {
	E_LOGIN, E_LOBBY, E_STAGE1,
};

class Scene
{
	vector<vector<int>> scene;
	unordered_map<unsigned long long, shared_ptr<Object>> objects;

	static unsigned long long global_id;
	static unsigned long long global_effect_id;

	list<shared_ptr<Object>> createQueue;
	list<unsigned long long> removeQueue;

	unsigned long long my_id = 0;

	AnimationMGR* animationMGR;
	E_SCENE sceneType;
public:
	static Scene* MainScene;
public:
	Scene();
	virtual ~Scene();

	virtual void Initialize();
	virtual void Update(double elapsedTime);
	virtual void Render();

	shared_ptr<Object> AddObject(Vec2 pos, int type);
	shared_ptr<Object> AddMonster(Vec2 pos, int type);
	shared_ptr<Object> AddSkill(Vec2 pos, int type, double holdingTime);
	shared_ptr<Object> AddSkill(Vec2 pos, int type, float animateSpeed, double holdingTime);

	void RemoveObject(unsigned long long id);

	vector<unsigned long long> CollideCheck(Vec2 position);
	vector<unsigned long long> CollideCheckForType(Vec2 position);
};

