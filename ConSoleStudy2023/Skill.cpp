#include "Skill.h"

Skill::Skill()
{
}

Skill::Skill(Vec2 Pos, unsigned long long id, int Time) : Object(Pos, id), durationTime(Time)
{
}

Skill::~Skill()
{
}

void Skill::Update()
{
	durationTime -= 0.01f;
	if (durationTime < 0.0) {
		removed = true;
	}
}
