#include "AttackComponent.h"

void AttackComponent::Start()
{
	AttackDamage = 10.f;
	AttackCoolTime = 1.f;
	AttackCoolTimeTimer = 0.f;
	b_Attack_able = false;
}

void AttackComponent::Update(double elapsedTime)
{
	if (false == b_Attack_able) {
		AttackCoolTimeTimer += elapsedTime;
		if (AttackCoolTimeTimer >= AttackCoolTime) {
			AttackCoolTimeTimer = 0.0;
			b_Attack_able = true;
		}
	}
}

void AttackComponent::SetAttackable(bool b)
{
	b_Attack_able = b;
}

void AttackComponent::SetAttackTimer(double d)
{
	AttackCoolTimeTimer = d;
}

bool AttackComponent::GetAttackable()
{
	return b_Attack_able;
}

float AttackComponent::GetAttackDamage()
{
	return AttackDamage;
}