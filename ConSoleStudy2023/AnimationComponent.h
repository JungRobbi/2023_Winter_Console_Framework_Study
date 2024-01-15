#pragma once
#include "Component.h"
class AnimationComponent :
    public Component
{
public:
    void Start();
    void Update(double elapsedTime);
};
