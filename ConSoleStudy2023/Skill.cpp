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

void Skill::Update()
{
	Object::Update();
	durationTime = animationTime;
	if (durationTime >= durationTimeMAX) {
		removed = true;
	}
}
