#pragma once
#include "Object.h"
#include "MonsterFSM.h"

class Monster
	: public Object
{
	shared_ptr<Object> target{ nullptr };

public:
	static shared_ptr<FSM> monsterFSM;
public:
	Monster();
	Monster(Vec2 Pos, int type, unsigned long long id);
	~Monster();

	void Update(double elapsedTime);

	void SetTarget(shared_ptr<Object> tar);
};
