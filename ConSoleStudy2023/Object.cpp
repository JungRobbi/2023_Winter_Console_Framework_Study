#include "Object.h"

Object::Object() : position{ 0, 0 }, object_id(0), direction(E_RIGHT)
{
}

Object::Object(Vec2 Pos, unsigned long long id) : position(Pos), object_id(id), direction(E_RIGHT)
{
}

Object::~Object()
{
}

Vec2 Object::GetPos()
{
	return position;
}

void Object::Update(double elapsedTime)
{
	animationTime += elapsedTime * animationSpeed;
	if (animationTime >= animationStateMAX) {
		animationTime -= animationStateMAX;
	}
	animationState = (int)animationTime;

	if (false == b_Attack_able) {
		AttackCoolTimeTimer += elapsedTime;
		if (AttackCoolTimeTimer >= AttackCoolTime) {
			AttackCoolTimeTimer = 0.0;
			b_Attack_able = true;
		}
	}

	if (false == b_Move_able) {
		MovementCoolTimeTimer += elapsedTime;
		if (MovementCoolTimeTimer >= MovementCoolTime) {
			MovementCoolTimeTimer = 0.0;
			b_Move_able = true;
		}
	}
}

void Object::SetPos(Vec2 pos)
{
	position = pos;
}

unsigned long long Object::GetId()
{
	return object_id;
}

void Object::SetId(int id)
{
	object_id = id;
}

E_DIRECTION Object::GetDirection()
{
	return direction;
}

void Object::SetDirection(E_DIRECTION dir)
{
	direction = dir;
}

bool Object::GetRemoved() {
	return removed;
}

int Object::GetType() 
{ 
	return objectType;
}

int Object::GetAnimationState()
{ 
	return animationState;
}

void Object::SetAnimationStateMAX(int i)
{ 
	animationStateMAX = i;
}

void Object::Move(E_DIRECTION dir, int step)
{
	switch (dir)
	{
	case E_UP:
		position.y -= 1;
		break;
	case E_DOWN:
		position.y += 1;
		break;
	case E_LEFT:
		position.x -= 1;
		break;
	case E_RIGHT:
		position.x += 1;
		break;
	default:
		break;
	}
	direction = dir;
}

void Object::SetAnimationSpeed(float f)
{ 
	animationSpeed = f;
}

void Object::SetAttackable(bool b)
{
	b_Attack_able = b;
}

void Object::SetMoveable(bool b)
{
	b_Move_able = b;
}

bool Object::GetAttackable()
{ 
	return b_Attack_able;
}

bool Object::GetMoveable()
{ 
	return b_Move_able;
}

void Object::SetMoveTimer(double d)
{
	MovementCoolTimeTimer = d;
}

void Object::SetAttackTimer(double d)
{
	AttackCoolTimeTimer = d;
}