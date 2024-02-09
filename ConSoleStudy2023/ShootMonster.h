#pragma once
#include "Monster.h"
class ShootMonster :
    public Monster
{
public:
	ShootMonster();
	ShootMonster(Vec2 Pos, int type, unsigned long long id);
	~ShootMonster();

	void Start();
	void Update(double elapsedTime);
};

