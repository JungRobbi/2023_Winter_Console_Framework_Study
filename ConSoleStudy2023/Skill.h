#pragma once
#include "Object.h"

class Skill :
    public Object
{
    double durationTime = 0.0;
    double durationTimeMAX = 10.0;
public:
    Skill();
    Skill(Vec2 Pos, int type, unsigned long long id, int Time);
    ~Skill();

    void Update(double elapsedTime);
};

