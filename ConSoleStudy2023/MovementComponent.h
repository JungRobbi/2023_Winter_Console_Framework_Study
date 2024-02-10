#pragma once
#include "Component.h"
#include "stdafx.h"

class MovementComponent :
    public Component
{
    double MovementCoolTime = 1.f;
    double MovementCoolTimeTimer = 0.f;
    bool b_Move_able = false;
public:
    void Start();
    void Update(double elapsedTime);

    bool GetMoveable();
    void SetMoveable(bool b);
    void SetMoveTimer(double d);
    void SetCoolTime(double d);
};
