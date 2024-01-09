#pragma once
#include "Object.h"
#include "FSM.h"

class Monster
	: public Object
{
	shared_ptr<Object> target{ nullptr };
	shared_ptr<FSM> monsterFSM;
public:
	Monster();
	Monster(Vec2 Pos, int type, unsigned long long id);
	~Monster();

	void Update(double elapsedTime);

	void SetTarget(shared_ptr<Object> tar);
};
