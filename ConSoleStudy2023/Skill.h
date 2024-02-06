#pragma once
#include "Object.h"

class Skill :
    public Object
{
    double durationTime = 0.0;
    double durationTimeMAX = 10.0;
    float animateSpeed;
    double holdingTime;
public:
    Skill();
    Skill(Vec2 Pos, int type, unsigned long long id, double Time);
    Skill(Vec2 Pos, int type, unsigned long long id, double Time, float aniSpeed);
    ~Skill();

    void Start();
    void Update(double elapsedTime);
};

