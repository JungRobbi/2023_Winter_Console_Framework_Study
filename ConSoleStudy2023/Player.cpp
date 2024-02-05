#include "Player.h"
#include "PlayerMovementComponent.h"
#include "StatusComponent.h"
#include "AnimationComponent.h"
#include "AnimationMGR.h"

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
	auto& animationMGR = AnimationMGR::GetInstance();
	auto pMComponent = AddComponent<PlayerMovementComponent>();
	pMComponent->SetPlayer(this);
	auto component = AddComponent<AnimationComponent>();
	component->SetAnimationStateMAX(animationMGR.GetAnimationShape(E_OBJECT::E_CLIENT).size());
	component->SetAnimationSpeed(2.f);
	AddComponent<StatusComponent>()->SetSight(10);
}

void Player::Update(double elapsedTime)
{
	Object::Update(elapsedTime);
}
