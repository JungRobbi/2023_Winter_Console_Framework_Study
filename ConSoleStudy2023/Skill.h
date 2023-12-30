#pragma once
#include "Object.h"

class Skill :
    public Object
{
    float durationTime;
public:
    Skill();
    Skill(Vec2 Pos, unsigned long long id, int Time);
    ~Skill();

    void Update();
};

