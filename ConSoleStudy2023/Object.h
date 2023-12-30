#pragma once
#include "stdafx.h"

struct Vec2 {
	int x, y;
};

class Object
{
	Vec2 position;
	unsigned long long object_id;
public:
	Object();
	Object(Vec2 Pos, unsigned long long id);
	virtual ~Object();

	unsigned long long GetId();
	void SetId(int id);
};

