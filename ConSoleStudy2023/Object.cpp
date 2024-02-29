#include "Object.h"
#include "Scene.h"

Object::Object() : position{ 0, 0 }, object_id(0), direction(E_DIRECTION::E_RIGHT)
{
}

Object::Object(Vec2 Pos, unsigned long long id) : position(Pos), object_id(id), direction(E_DIRECTION::E_RIGHT)
{
}

Object::Object(Vec2 Pos, int type, unsigned long long id) : position(Pos), object_id(id), direction(E_DIRECTION::E_RIGHT)
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
		if (objectType >= E_OBJECT::E_EFFECT)
			break;

		if (Scene::MainScene->GetObjectType(collideId) >= E_OBJECT::E_ITEM)
			continue;		
		return;
	}
	position += dir;
	direction = dir;
}

void Object::MoveUncond(E_DIRECTION dir, int step)
{
	position += dir;
	direction = dir;
}