#pragma once
#include "Object.h"

class Player
	: public Object
{

public:
	Player();
	Player(Vec2 Pos, int type, unsigned long long id);
	~Player();

	void Start();
	void Update(double elapsedTime) final;
};

