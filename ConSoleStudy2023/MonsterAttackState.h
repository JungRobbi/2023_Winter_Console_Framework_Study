#pragma once
#include "FSMState.h"
#include "Monster.h"

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


				cout << "                         ATTACK!" << endl;
				dynamic_cast<Monster*>(owner)->SetFSMState(E_FSM_STATE::E_FSM_WANDER);
			}
		}
	}
	void Exit(Object* owner)
	{
	}
};