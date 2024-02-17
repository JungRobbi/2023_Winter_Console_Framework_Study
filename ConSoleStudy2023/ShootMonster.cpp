#include "ShootMonster.h"

#include "MovementComponent.h"
#include "StatusComponent.h"
#include "AttackComponent.h"
#include "AnimationComponent.h"
#include "AnimationMGR.h"

#include "ShootWanderState.h"
#include "ShootAttackState.h"
#include "ShootTrackingState.h"

ShootMonster::ShootMonster()
	: Monster()
{
}

ShootMonster::ShootMonster(Vec2 Pos, int type, unsigned long long id)
	: Monster(Pos, type, id)
{
}

ShootMonster::~ShootMonster()
{
}

void ShootMonster::Start()
{
	monsterFSM = make_shared<FSM>(this, make_shared<ShootWanderState>());
	flag = E_FSM_STATE::E_FSM_WANDER;
	currentState = E_FSM_STATE::E_FSM_WANDER;

	//AddComponent
	AddComponent<MovementComponent>();
	AddComponent<AttackComponent>();
	AddComponent<StatusComponent>();
	AddComponent<AnimationComponent>();

	Object::Start();

	// Component °ª º¯°æ
	{
		auto& animationMGR = AnimationMGR::GetInstance();
		{
			auto component = GetComponent<AnimationComponent>();
			component->SetAnimationStateMAX(animationMGR.GetAnimationShape(objectType).size());
		}
		{
			auto component = GetComponent<StatusComponent>();
			component->SetSight(5);
		}
	}
}

void ShootMonster::Update(double elapsedTime)
{
	Object::Update(elapsedTime);

	if (monsterFSM) {
		if (currentState != flag) {
			currentState = flag;
			switch (flag)
			{
			case E_FSM_STATE::E_FSM_WANDER:
				monsterFSM->ChangeState(std::make_shared<ShootWanderState>());
				break;
			case E_FSM_STATE::E_FSM_TRACKING:
				monsterFSM->ChangeState(std::make_shared<ShootTrackingState>());
				break;
			case E_FSM_STATE::E_FSM_ATTACK:
				monsterFSM->ChangeState(std::make_shared<ShootAttackState>());
				break;
			default:
				break;
			}
		}

		monsterFSM->Update(elapsedTime);
	}
}
