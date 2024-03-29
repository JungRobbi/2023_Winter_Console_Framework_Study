#pragma once
#include "stdafx.h"
#include "FSMState.h"
#include "Monster.h"

#include "MovementComponent.h"
#include "StatusComponent.h"

class ShootTrackingState :
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

				auto target = dynamic_cast<Monster*>(owner)->GetTarget();
				if (target) {
					auto targetPos = target->GetPos();
					auto owner_pos = owner->GetPos();
					E_DIRECTION dir;
					Vec2 dirVec2 = targetPos - owner_pos;
					if ((abs(dirVec2.x) < abs(dirVec2.y) && dirVec2.x != 0) || dirVec2.y == 0)
						if (dirVec2.x < 0)
							dir = E_DIRECTION::E_LEFT;
						else
							dir = E_DIRECTION::E_RIGHT;
					else
						if (dirVec2.y < 0)
							dir = E_DIRECTION::E_UP;
						else
							dir = E_DIRECTION::E_DOWN;

					switch (dir)
					{
					case E_DIRECTION::E_UP:
						if (owner_pos.y - 1 < 0)
							return;
						break;
					case E_DIRECTION::E_DOWN:
						if (owner_pos.y + 1 >= MapSize::CURRENT_MAP_SIZE.y)
							return;
						break;
					case E_DIRECTION::E_LEFT:
						if (owner_pos.x - 1 < 0)
							return;
						break;
					case E_DIRECTION::E_RIGHT:
						if (owner_pos.x + 1 >= MapSize::CURRENT_MAP_SIZE.x)
							return;
						break;
					default:
						break;
					}
					owner->Move(dir, 1);
					auto pos = target->GetPos();
					if (3 >= DistanceVec2(pos, owner->GetPos())) {
						dynamic_cast<Monster*>(owner)->SetFSMState(E_FSM_STATE::E_FSM_ATTACK);
					}
					else if (owner->GetComponent<StatusComponent>()->GetSight() < DistanceVec2(pos, owner->GetPos())) {
						dynamic_cast<Monster*>(owner)->SetFSMState(E_FSM_STATE::E_FSM_WANDER);
					}
				}
			}
		}
	}
	void Exit(Object* owner)
	{
	}
};

