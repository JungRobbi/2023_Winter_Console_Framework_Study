#pragma once
#include "FSMState.h"
#include "Monster.h"
#include "Skill.h"
#include "Scene.h"

class MonsterAttackState :
	public FSMState
{
public:
	void Enter(Object* owner)
	{
	}
	void Execute(Object* owner)
	{
		if (dynamic_cast<Monster*>(owner)) {
			if (owner->GetAttackable()) {
				owner->SetAttackable(false);
				owner->SetAttackTimer(0.0);

				Vec2 my_pos = owner->GetPos();
				E_DIRECTION my_dir = owner->GetDirection();

			//	AddSkill();

				cout << "                         ATTACK!" << endl;
				dynamic_cast<Monster*>(owner)->SetFSMState(E_FSM_STATE::E_FSM_WANDER);
			}
		}
	}
	void Exit(Object* owner)
	{
	}
};