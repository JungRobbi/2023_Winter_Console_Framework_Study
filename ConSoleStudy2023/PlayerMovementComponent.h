#pragma once
#include "MovementComponent.h"
#include <memory>
class Object;

class PlayerMovementComponent :
    public MovementComponent
{
    std::shared_ptr<Object> object;
public:
    void Start();
    void Update(double elapsedTime);

    void SetPlayer(std::shared_ptr<Object> player);
};
