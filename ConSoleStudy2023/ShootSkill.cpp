#include "ShootSkill.h"
#include "Scene.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"

ShootSkill::ShootSkill() : Skill()
{
	objectType = E_OBJECT::E_EFFECT;
}

ShootSkill::ShootSkill(Vec2 Pos, int type, unsigned long long id, double Time) : Skill(Pos, type, id, Time)
{
	objectType = type;
}

ShootSkill::ShootSkill(Vec2 Pos, int type, unsigned long long id, double Time, float aniSpeed) : Skill(Pos, type, id, Time, aniSpeed)
{
	objectType = type;
}

ShootSkill::~ShootSkill()
{
}

void ShootSkill::Start()
{
	//AddComponent
	AddComponent<AnimationComponent>();
	AddComponent<MovementComponent>();


	Object::Start();

	// Component °ª º¯°æ
	{
		auto& animationMGR = AnimationMGR::GetInstance();
		{
			auto component = GetComponent<AnimationComponent>();
			component->SetAnimationStateMAX(animationMGR.GetAnimationShape(objectType).size());
			component->SetAnimationSpeed(animateSpeed);
		}
		{
			auto component = GetComponent<MovementComponent>();
			component->SetCoolTime(0.1);
		}
	}
}

void ShootSkill::Update(double elapsedTime)
{
	Skill::Update(elapsedTime);

	auto movementComponent = GetComponent<MovementComponent>();
	if (movementComponent) {
		if (movementComponent->GetMoveable()) {
			Move(direction, 1);
			movementComponent->SetMoveable(false);
		}
	}
}