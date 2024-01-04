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
	Object::Update();
	durationTime -= 0.01f;
	if (durationTime < 0.0) {
		removed = true;
	}
}
