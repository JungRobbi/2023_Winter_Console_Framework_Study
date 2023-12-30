#include "Object.h"

Object::Object() : position{ 0, 0 }, object_id(0)
{
}

Object::Object(Vec2 Pos, unsigned long long id) : position(Pos), object_id(id)
{
}

Object::~Object()
{
}

Vec2 Object::GetPos()
{
	return position;
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
