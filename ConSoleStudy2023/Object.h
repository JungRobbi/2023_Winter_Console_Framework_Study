#pragma once
#include "stdafx.h"

enum E_OBJECT {
	E_CLIENT = 0,
	E_ENEMY = 10000,
	E_WALL = 20000,
	E_ITEM = 20100,
	E_TILE = 20200,
	E_EFFECT = 30000,
	E_EFFECT_ATTACK = 40000,
};

static random_device rd;
static default_random_engine dre(rd());
static uniform_int_distribution<int> rand_dirUid(0, 3);

class Object
{
protected:
	Vec2 position;
	E_DIRECTION direction;
	unsigned long long object_id;
	int objectType = -1;

	int animationState = 0;
	int animationStateMAX = 1;
	double animationTime = 0.f;
	float animationSpeed = 1.f;

	float HP = 100.f;
	float HPMAX = 100.f;
	float AttackDamage = 10.f;
	double AttackCoolTime = 1.f;
	double MovementCoolTime = 1.f;
	float Defence = 1.f;

	double AttackCoolTimeTimer = 0.f;
	double MovementCoolTimeTimer = 0.f;
	bool b_Attack_able = false;
	bool b_Move_able = false;
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

	int GetType();
	int GetAnimationState();

	void SetAnimationStateMAX(int i);
	void SetAnimationSpeed(float f);

	bool GetAttackable();
	bool GetMoveable();
	void SetAttackable(bool b);
	void SetMoveable(bool b);


	void SetMoveTimer(double d);
	void SetAttackTimer(double d);

	void Move(E_DIRECTION dir, int step);
};

