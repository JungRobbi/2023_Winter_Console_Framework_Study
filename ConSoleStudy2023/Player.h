#pragma once
#include "Object.h"

class Player
	: public Object
{

public:
	Player();
	Player(Vec2 Pos, int type, unsigned long long id);
	~Player();

	void Update(double elapsedTime);
};

