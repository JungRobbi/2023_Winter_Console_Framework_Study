#pragma once
#include "stdafx.h"

struct Vec2 {
	int x, y;
};

enum E_DIRECTION {
	E_UP, E_DOWN, E_LEFT, E_RIGHT
};

class Object
{
protected:
	Vec2 position;
	E_DIRECTION direction;
	unsigned long long object_id;

	bool removed;
public:
	Object();
	Object(Vec2 Pos, unsigned long long id);
	virtual ~Object();

	virtual void Update();

	Vec2 GetPos();
	void SetPos(Vec2 pos);

	unsigned long long GetId();
	void SetId(int id);

	E_DIRECTION GetDirection();
	void SetDirection(E_DIRECTION pos);

	bool GetRemoved();
};

