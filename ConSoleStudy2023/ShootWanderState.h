#pragma once
#include "stdafx.h"
#include "FSMState.h"
#include "Monster.h"

#include "MovementComponent.h"
#include "StatusComponent.h"

class ShootWanderState :
    public FSMState
{
public:
	void Enter(Object* owner)
	{
	}
	void Execute(Object* owner)
	{
		if (dynamic_cast<Monster*>(owner)) {
			if (owner->GetComponent<MovementComponent>()->GetMoveable()) {
				owner->GetComponent<MovementComponent>()->SetMoveable(false);
				owner->GetComponent<MovementComponent>()->SetMoveTimer(0.0);

				E_DIRECTION dir = (E_DIRECTION)(rand_dirUid(dre));
				auto owner_pos = owner->GetPos();
				switch (dir)
				{
				case E_DIRECTION::E_UP:
					if (owner_pos.y - 1 < 0)
						return;
					break;
				case E_DIRECTION::E_DOWN:
					if (owner_pos.y + 1 >= CURRENT_MAP_SIZE.y)
						return;
					break;
				case E_DIRECTION::E_LEFT:
					if (owner_pos.x - 1 < 0)
						return;
					break;
				case E_DIRECTION::E_RIGHT:
					if (owner_pos.x + 1 >= CURRENT_MAP_SIZE.x)
						return;
					break;
				default:
					break;
				}
				owner->Move(dir, 1);
				auto target = dynamic_cast<Monster*>(owner)->GetTarget();
				if (target) {
					auto pos = target->GetPos();
					if (owner->GetComponent<StatusComponent>()->GetSight() >= DistanceVec2(pos, owner->GetPos())) {
						dynamic_cast<Monster*>(owner)->SetFSMState(E_FSM_STATE::E_FSM_TRACKING);
					}
				}
			}
		}
	}
	void Exit(Object* owner)
	{
	}
};

