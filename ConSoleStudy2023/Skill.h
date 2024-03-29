#pragma once
#include "Object.h"

class Skill :
    public Object
{
protected:
    double durationTime = 0.0;
    double durationTimeMAX = 10.0;
    float animateSpeed;
    double holdingTime;
public:
    Skill();
    Skill(Vec2 Pos, int type, unsigned long long id, double Time);
    Skill(Vec2 Pos, int type, unsigned long long id, double Time, float aniSpeed);
    virtual ~Skill();

    virtual void Start();
    virtual void Update(double elapsedTime);
};

