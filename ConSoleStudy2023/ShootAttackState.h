#pragma once
#include "stdafx.h"
#include "FSMState.h"
#include "Monster.h"
#include "Skill.h"
#include "Scene.h"

#include "AttackComponent.h"

class ShootAttackState :
    public FSMState
{
public:
	void Enter(Object* owner)
	{
	}
	void Execute(Object* owner)
	{
		if (dynamic_cast<Monster*>(owner)) {
			if (owner->GetComponent<AttackComponent>()->GetAttackable()) {
				owner->GetComponent<AttackComponent>()->SetAttackable(false);
				owner->GetComponent<AttackComponent>()->SetAttackTimer(0.0);

				auto target = dynamic_cast<Monster*>(owner)->GetTarget();
				if (target) {
					auto targetPos = target->GetPos();
					Vec2 my_pos = owner->GetPos();

					E_DIRECTION dir;
					Vec2 dirVec2 = targetPos - my_pos;
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

					owner->SetDirection(dir);
					E_DIRECTION my_dir = owner->GetDirection();
					auto p = my_pos + my_dir;
					if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
						p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
						Scene::MainScene->AddShootSkill(p, E_OBJECT::E_EFFECT + 2, 1.f, 5.0, my_dir);
					}

					auto pos = target->GetPos();
					if (1 < DistanceVec2(pos, my_pos)) {
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

