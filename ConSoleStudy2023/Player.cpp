#include "Player.h"
#include "PlayerMovementComponent.h"
#include "StatusComponent.h"
#include "AnimationComponent.h"
#include "AnimationMGR.h"
#include "AttackComponent.h"
#include "InventoryComponent.h"

Player::Player() : Object()
{
	objectType = E_OBJECT::E_CLIENT;
}

Player::Player(Vec2 Pos, int type, unsigned long long id) : Object(Pos, id)
{
	objectType = type;
}

Player::~Player()
{
}

void Player::Start()
{
	//AddComponent
	AddComponent<PlayerMovementComponent>();
	AddComponent<AnimationComponent>();
	AddComponent<StatusComponent>();
	AddComponent<AttackComponent>();
	AddComponent<InventoryComponent>();

	Object::Start();

	// Component °ª º¯°æ
	{
		auto& animationMGR = AnimationMGR::GetInstance();
		{
			auto component = GetComponent<PlayerMovementComponent>();
			component->SetPlayer(this);
		}
		{
			auto component = GetComponent<AnimationComponent>();
			component->SetAnimationStateMAX(animationMGR.GetAnimationShape(E_OBJECT::E_CLIENT).size());
			component->SetAnimationSpeed(2.f);
		}
		GetComponent<StatusComponent>()->SetSight(10);
		GetComponent<AttackComponent>();
	}
}

void Player::Update(double elapsedTime)
{
	Object::Update(elapsedTime);
}
