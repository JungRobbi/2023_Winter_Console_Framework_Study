#pragma once
#include "Component.h"

class MovementComponent :
    public Component
{
public:
    void Start();
    void Update(double elapsedTime);
};
