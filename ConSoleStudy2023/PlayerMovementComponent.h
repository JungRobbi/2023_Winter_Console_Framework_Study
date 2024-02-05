#pragma once
#include "MovementComponent.h"
class Object;

class PlayerMovementComponent :
    public MovementComponent
{
    Object* object;
public:
    void Start();
    void Update(double elapsedTime);

    void SetPlayer(Object* player);
};
