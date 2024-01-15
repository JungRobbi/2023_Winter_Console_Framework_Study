#include "Skill.h"
#include "Scene.h"
#include "AnimationComponent.h"

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
	/*auto animationComponent = GetComponent<AnimationComponent>();

	if (animationComponent->GetAnimationState() + 1
		== animationComponent->GetAnimationStateMAX()) {
		Scene::MainScene->RemoveObject(object_id);
		return;
	}*/

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
