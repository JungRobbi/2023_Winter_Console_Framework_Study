#include "AnimationComponent.h"

void AnimationComponent::Start()
{
}

void AnimationComponent::Update(double elapsedTime)
{
	animationTime += elapsedTime * animationSpeed;
	if (animationTime >= animationStateMAX) {
		animationTime -= animationStateMAX;
	}
	animationState = (int)animationTime;
}

int AnimationComponent::GetAnimationState()
{
	return animationState;
}

int AnimationComponent::GetAnimationStateMAX()
{
	return animationStateMAX;
}

double AnimationComponent::GetAnimationTime()
{
	return animationTime;
}

float AnimationComponent::GetAnimationSpeed()
{
	return animationSpeed;
}

void AnimationComponent::SetAnimationStateMAX(int i)
{
	animationStateMAX = i;
}
void AnimationComponent::SetAnimationSpeed(float f)
{
	animationSpeed = f;
}
