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
	Object::Update(elapsedTime);
	auto animationComponent = GetComponent<AnimationComponent>();
	if (animationComponent) {
		double currentTime = animationComponent->GetAnimationTime();
		if (currentTime + elapsedTime * animationComponent->GetAnimationSpeed()
			>= animationComponent->GetAnimationStateMAX()) {
			Scene::MainScene->RemoveObject(object_id);
		}
	}
}
