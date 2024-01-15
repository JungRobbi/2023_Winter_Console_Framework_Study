#pragma once
#include "MovementComponent.h"

class PlayerMovementComponent :
    public MovementComponent
{
public:
    void Start();
    void Update(double elapsedTime);
};
