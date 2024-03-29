#pragma once
#include "Component.h"
#include <stdlib.h>
class AnimationComponent :
    public Component
{
    int animationState = 0;
    int animationStateMAX = 1;
    double animationTime = 0.f;
    float animationSpeed = 1.f;
public:
    void Start();
    void Update(double elapsedTime);

    int GetAnimationState();
    int GetAnimationStateMAX();
    double GetAnimationTime();
    float GetAnimationSpeed();

    void SetAnimationStateMAX(int i);
    void SetAnimationSpeed(float f);
};
