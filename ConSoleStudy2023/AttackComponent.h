#pragma once
#include "Component.h"
class AttackComponent :
    public Component
{
public:
    void Start();
    void Update(double elapsedTime);
};

