#include "Skill.h"

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
	Object::Update(elapsedTime);
	durationTime = animationTime;
	if (durationTime >= durationTimeMAX) {
		removed = true;
	}
}
