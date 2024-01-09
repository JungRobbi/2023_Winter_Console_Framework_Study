#include "Monster.h"

shared_ptr<FSM> Monster::monsterFSM = make_shared<MonsterFSM>();

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

void Monster::Update(double elapsedTime)
{
	Object::Update(elapsedTime);

	if (monsterFSM) {
		monsterFSM->Update(elapsedTime, this);
	}

	//if (b_Move_able) {
	//	b_Move_able = false;
	//	MovementCoolTimeTimer = 0.0;

	//	E_DIRECTION dir = (E_DIRECTION)(rand_dirUid(dre));
	//	switch (dir)
	//	{
	//	case E_UP:
	//		if (position.y - 1 < 0)
	//			return;
	//		break;
	//	case E_DOWN:
	//		if (position.y + 1 >= StageSizeY)
	//			return;
	//		break;
	//	case E_LEFT:
	//		if (position.x - 1 < 0)
	//			return;
	//		break;
	//	case E_RIGHT:
	//		if (position.x + 1 >= StageSizeX)
	//			return;
	//		break;
	//	default:
	//		break;
	//	}

	//	Move(dir, 1);
	//}
}

void Monster::SetTarget(shared_ptr<Object> tar)
{
	target = tar;
}
