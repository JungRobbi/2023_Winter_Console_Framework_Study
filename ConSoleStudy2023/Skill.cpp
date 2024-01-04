#include "Skill.h"

Skill::Skill() : Object()
{
	objectType = E_OBJECT::E_EFFECT;
}

Skill::Skill(Vec2 Pos, int type, unsigned long long id, int Time) : Object(Pos, id), durationTime(Time)
{
	objectType = type;
}

Skill::~Skill()
{
}

void Skill::Update()
{
	durationTime -= 0.01f;
	animationTime += 0.001f * animationSpeed;
	if (durationTime < 0.0 || animationTime > animationStateMAX) {
		removed = true;
		return;
	}
	animationState = (int)animationTime;

}
