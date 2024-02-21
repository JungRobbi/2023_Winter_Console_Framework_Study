#include "Item.h"
#include "AnimationComponent.h"
#include "AnimationMGR.h"


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
	AddComponent<AnimationComponent>();


	Object::Start();

	// Component °ª º¯°æ
	{
		auto& animationMGR = AnimationMGR::GetInstance();
		{
			auto component = GetComponent<AnimationComponent>();
			component->SetAnimationStateMAX(animationMGR.GetAnimationShape(objectType).size());
			component->SetAnimationSpeed(1.f);
		}
	}

}

void Item::Update(double elapsedTime)
{
	Object::Update(elapsedTime);
}
