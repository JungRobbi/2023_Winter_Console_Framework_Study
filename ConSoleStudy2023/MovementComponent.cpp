#include "MovementComponent.h"

#include "Scene.h"

void MovementComponent::Start()
{
	MovementCoolTime = 1.f;
	MovementCoolTimeTimer = 0.f;
	b_Move_able = false;
}

void MovementComponent::Update(double elapsedTime)
{
	if (false == b_Move_able) {
		MovementCoolTimeTimer += elapsedTime;
		if (MovementCoolTimeTimer >= MovementCoolTime) {
			MovementCoolTimeTimer = 0.0;
			b_Move_able = true;
		}
	}
}

void MovementComponent::SetMoveable(bool b)
{
	b_Move_able = b;
}

bool MovementComponent::GetMoveable()
{
	return b_Move_able;
}

void MovementComponent::SetMoveTimer(double d)
{
	MovementCoolTimeTimer = d;
}

void MovementComponent::SetCoolTime(double d)
{
	MovementCoolTime = d;
}
