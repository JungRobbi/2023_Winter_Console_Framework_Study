#include "Monster.h"

Monster::Monster() : Object()
{
	objectType = E_OBJECT::E_CLIENT;
}

Monster::Monster(Vec2 Pos, int type, unsigned long long id) : Object(Pos, id)
{
	objectType = type;
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Object::Update();
}

void Monster::SetTarget(shared_ptr<Object> tar)
{
	target = tar;
}
