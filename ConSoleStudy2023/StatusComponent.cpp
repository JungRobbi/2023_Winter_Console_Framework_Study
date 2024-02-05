#include "StatusComponent.h"

void StatusComponent::Start()
{
	HP = 100.f;
	HPMAX = 100.f;
	Defence = 1.f;
	sight = 3;
}

void StatusComponent::Update(double elapsedTime)
{
}

float StatusComponent::GetHP()
{
	return HP;
}

float StatusComponent::GetHPMAX()
{
	return HPMAX;
}

float StatusComponent::GetDefence()
{
	return Defence;
}

int StatusComponent::GetSight()
{
	return sight;
}

void StatusComponent::SetSight(int i)
{
	sight = i;
}

void StatusComponent::HitDamage(float damage)
{
	HP -= damage / Defence;
	if (HP < 0.f)
		HP = 0.f;
}
