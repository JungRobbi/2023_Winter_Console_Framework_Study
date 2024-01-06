#pragma once
#include "Object.h"

class Skill :
    public Object
{
    float durationTime = 0.f;
    float durationTimeMAX = 10.f;
public:
    Skill();
    Skill(Vec2 Pos, int type, unsigned long long id, int Time);
    ~Skill();

    void Update();
};

