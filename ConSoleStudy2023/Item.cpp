#include "Item.h"


Item::Item() : Object()
{
	objectType = E_OBJECT::E_CLIENT;
}

Item::Item(Vec2 Pos, int type, unsigned long long id) : Object(Pos, id)
{
	objectType = type;
}

Item::~Item()
{
}

void Item::Start()
{
	//AddComponent

	Object::Start();

	// Component °ª º¯°æ

}

void Item::Update(double elapsedTime)
{
	Object::Update(elapsedTime);
}
