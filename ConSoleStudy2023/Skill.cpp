#include "Skill.h"
#include "Scene.h"

Skill::Skill() : Object()
{
	objectType = E_OBJECT::E_EFFECT;
}

Skill::Skill(Vec2 Pos, int type, unsigned long long id, int Time) : Object(Pos, id), durationTimeMAX(Time)
{
	objectType = type;
}

Skill::~Skill()
{
}

void Skill::Update(double elapsedTime)
{
	animationTime += elapsedTime * animationSpeed;
	if (animationTime >= animationStateMAX) {
		animationTime -= animationStateMAX;
		Scene::MainScene->RemoveObject(object_id);
		return;
	}
	animationState = (int)animationTime;

	if (false == b_Attack_able) {
		AttackCoolTimeTimer += elapsedTime;
		if (AttackCoolTimeTimer >= AttackCoolTime) {
			AttackCoolTimeTimer = 0.0;
			b_Attack_able = true;
		}
	}

	if (false == b_Move_able) {
		MovementCoolTimeTimer += elapsedTime;
		if (MovementCoolTimeTimer >= MovementCoolTime) {
			MovementCoolTimeTimer = 0.0;
			b_Move_able = true;
		}
	}
}
