#pragma once
#include "stdafx.h"
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
				auto p = my_pos + my_dir;
				if (p.x >= 0 && p.x < StageSizeX &&
					p.y >= 0 && p.y < StageSizeY) {
					Scene::MainScene->AddSkill(p, E_OBJECT::E_EFFECT + 1, 1.f, 1.0);
				}
				auto target = dynamic_cast<Monster*>(owner)->GetTarget();
				if (target) {
					auto pos = target->GetPos();
					if (owner->GetSight() < DistanceVec2(pos, my_pos)) {
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