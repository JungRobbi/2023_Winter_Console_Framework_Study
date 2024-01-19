#include "Object.h"
#include "Scene.h"

Object::Object() : position{ 0, 0 }, object_id(0), direction(E_RIGHT)
{
}

Object::Object(Vec2 Pos, unsigned long long id) : position(Pos), object_id(id), direction(E_RIGHT)
{
}

Object::Object(Vec2 Pos, int type, unsigned long long id) : position(Pos), object_id(id), direction(E_RIGHT)
{
	objectType = type;
}

Object::~Object()
{
}

Vec2 Object::GetPos()
{
	return position;
}

void Object::Start()
{
	for (auto& component : components) 
		component->Start();
}

void Object::Update(double elapsedTime)
{
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

	for (auto& component : components)
		component->Update(elapsedTime);
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

int Object::GetType() 
{ 
	return objectType;
}

void Object::Move(E_DIRECTION dir, int step)
{
	auto colliderList = Scene::MainScene->CollideCheckForType(position + dir);
	for (auto collideId : colliderList) {
		if (collideId == E_OBJECT::E_CLIENT)
			continue;
		else
			return;
	}
	position += dir;
	direction = dir;
}

int Object::GetSight()
{
	return sight;
}

void Object::SetSight(int i)
{
	sight = i;
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