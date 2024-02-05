#pragma once
#include "Component.h"
class AttackComponent :
    public Component
{
    float AttackDamage;
    double AttackCoolTime;
    double AttackCoolTimeTimer;
    bool b_Attack_able;
public:
    void Start();
    void Update(double elapsedTime);

    void SetAttackable(bool b);
    void SetAttackTimer(double d);
    bool GetAttackable();
};