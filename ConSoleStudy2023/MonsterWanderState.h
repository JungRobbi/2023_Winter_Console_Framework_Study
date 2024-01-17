#pragma once
#include "stdafx.h"
#include "FSMState.h"
#include "Monster.h"

class MonsterWanderState :
    public FSMState
{
public:
    void Enter(Object* owner)
    { 
    }
    void Execute(Object* owner)
    {
		if (dynamic_cast<Monster*>(owner)) {
			if (owner->GetMoveable()) {
				owner->SetMoveable(false);
				owner->SetMoveTimer(0.0);

				E_DIRECTION dir = (E_DIRECTION)(rand_dirUid(dre));
				auto owner_pos = owner->GetPos();
				switch (dir)
				{
				case E_UP:
					if (owner_pos.y - 1 < 0)
						return;
					break;
				case E_DOWN:
					if (owner_pos.y + 1 >= STAGE_SIZE_Y)
						return;
					break;
				case E_LEFT:
					if (owner_pos.x - 1 < 0)
						return;
					break;
				case E_RIGHT:
					if (owner_pos.x + 1 >= STAGE_SIZE_X)
						return;
					break;
				default:
					break;
				}
				owner->Move(dir, 1);
				auto target = dynamic_cast<Monster*>(owner)->GetTarget();
				if (target) {
					auto pos = target->GetPos();
					if (owner->GetSight() >= DistanceVec2(pos, owner->GetPos())) {
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