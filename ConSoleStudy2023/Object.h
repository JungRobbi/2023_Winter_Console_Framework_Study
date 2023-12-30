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

	Vec2 GetPos();
	void SetPos(Vec2 pos);

	unsigned long long GetId();
	void SetId(int id);
};

