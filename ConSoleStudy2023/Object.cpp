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

void Object::Update()
{
	animationTime += 0.001f;
	if (animationTime >= animationStateMAX) {
		animationTime = 0.f;
	}
	animationState = (int)animationTime;
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

void Object::SetAnimationSpeed(float f)
{ 
	animationSpeed = f;
}