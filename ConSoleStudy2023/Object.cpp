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

unsigned long long Object::GetId()
{
	return object_id;
}

void Object::SetId(int id)
{
	object_id = id;
}
