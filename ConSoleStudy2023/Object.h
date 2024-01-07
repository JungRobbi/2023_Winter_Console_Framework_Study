#pragma once
#include "stdafx.h"

enum E_OBJECT {
	E_CLIENT = 0,
	E_ENEMY = 10000,
	E_TILE = 20000,
	E_WALL = 20100,
	E_ITEM = 20200,
	E_EFFECT = 30000,
};

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
	int objectType;

	bool removed;

	int animationState = 0;
	int animationStateMAX = 1;
	float animationTime = 0.f;
	float animationSpeed = 1.f;

	float HP = 100.f;
	float HPMAX = 100.f;
	float AttackDamage = 10.f;
	float AttackCoolTime = 1.f;
	float MovementCoolTime = 1.f;
	float Defence = 1.f;

public:
	Object();
	Object(Vec2 Pos, unsigned long long id);
	virtual ~Object();

	virtual void Update(double elapsedTime);

	Vec2 GetPos();
	void SetPos(Vec2 pos);

	unsigned long long GetId();
	void SetId(int id);

	E_DIRECTION GetDirection();
	void SetDirection(E_DIRECTION pos);

	bool GetRemoved();

	int GetType();
	int GetAnimationState();

	void SetAnimationStateMAX(int i);
	void SetAnimationSpeed(float f);


	void Move(E_DIRECTION dir, int step);
};

