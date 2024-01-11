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
	Object::Update(elapsedTime);
	durationTime += elapsedTime;
	if (durationTime >= durationTimeMAX) {
		Scene::MainScene->RemoveObject(object_id);
	}
}
