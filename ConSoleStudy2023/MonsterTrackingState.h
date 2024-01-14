#pragma once
#include "stdafx.h"
#include "FSMState.h"
#include "Monster.h"

class MonsterTrackingState :
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

				auto target = dynamic_cast<Monster*>(owner)->GetTarget();
				if (target) {
					auto targetPos = target->GetPos();
					auto owner_pos = owner->GetPos();
					E_DIRECTION dir;
					Vec2 dirVec2 = targetPos - owner_pos;
					if (abs(dirVec2.x) > abs(dirVec2.y)) 
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
					case E_UP:
						if (owner_pos.y - 1 < 0)
							return;
						break;
					case E_DOWN:
						if (owner_pos.y + 1 >= StageSizeY)
							return;
						break;
					case E_LEFT:
						if (owner_pos.x - 1 < 0)
							return;
						break;
					case E_RIGHT:
						if (owner_pos.x + 1 >= StageSizeX)
							return;
						break;
					default:
						break;
					}
					owner->Move(dir, 1);
					auto pos = target->GetPos();
					if (1 >= DistanceVec2(pos, owner->GetPos())) {
						dynamic_cast<Monster*>(owner)->SetFSMState(E_FSM_STATE::E_FSM_ATTACK);
					}
					else if (owner->GetSight() < DistanceVec2(pos, owner->GetPos())) {
						dynamic_cast<Monster*>(owner)->SetFSMState(E_FSM_STATE::E_FSM_ATTACK);
					}
				}
			}
		}
	}
	void Exit(Object* owner)
	{
	}
};