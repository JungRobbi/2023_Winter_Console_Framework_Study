#pragma once
#include "Skill.h"
class ShootSkill :
    public Skill
{
public:
    ShootSkill();
    ShootSkill(Vec2 Pos, int type, unsigned long long id, double Time);
    ShootSkill(Vec2 Pos, int type, unsigned long long id, double Time, float aniSpeed);
    ~ShootSkill();

    void Start();
    void Update(double elapsedTime);
};

