#pragma once
#include "Object.h"
class Item :
    public Object
{
public:
	Item();
	Item(Vec2 Pos, int type, unsigned long long id);
	~Item();

	void Start();
	void Update(double elapsedTime) final;
};

