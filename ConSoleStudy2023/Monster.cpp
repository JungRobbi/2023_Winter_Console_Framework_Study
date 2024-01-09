#include "Monster.h"
#include "MonsterWanderState.h"
Monster::Monster() : Object(), monsterFSM(make_shared<FSM>(this, make_shared<MonsterWanderState>()))
{
	objectType = E_OBJECT::E_CLIENT;
}

Monster::Monster(Vec2 Pos, int type, unsigned long long id) 
	: Object(Pos, id), monsterFSM(make_shared<FSM>(this, make_shared<MonsterWanderState>()))
{
	objectType = type;
}

Monster::~Monster()
{
}

void Monster::Update(double elapsedTime)
{
	Object::Update(elapsedTime);

	if (monsterFSM) {
		monsterFSM->Update(elapsedTime);
	}
}

void Monster::SetTarget(shared_ptr<Object> tar)
{
	target = tar;
}
