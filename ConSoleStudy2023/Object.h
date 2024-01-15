#pragma once
#include "stdafx.h"
#include "Component.h"

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
static uniform_real_distribution<float> rand_realUid(0, 1);

class Object
{
protected:
	Vec2 position;
	E_DIRECTION direction;
	unsigned long long object_id;
	int objectType = -1;

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

	int sight = 3;

	list<shared_ptr<Component>> components;
public:
	Object();
	Object(Vec2 Pos, unsigned long long id);
	virtual ~Object();

	virtual void Start();
	virtual void Update(double elapsedTime);

	Vec2 GetPos();
	void SetPos(Vec2 pos);

	unsigned long long GetId();
	void SetId(int id);

	E_DIRECTION GetDirection();
	void SetDirection(E_DIRECTION pos);

	int GetType();

	bool GetAttackable();
	bool GetMoveable();
	void SetAttackable(bool b);
	void SetMoveable(bool b);

	void SetMoveTimer(double d);
	void SetAttackTimer(double d);

	void Move(E_DIRECTION dir, int step);

	int GetSight();
	void SetSight(int i);

	template<class T>
	std::shared_ptr<T> AddComponent();

	template<class T>
	std::shared_ptr<T> GetComponent();
};

template<class T>
inline std::shared_ptr<T> Object::AddComponent()
{
	std::shared_ptr<T> component = make_shared<T>();
	components.push_back(component);
	return component;
}

template<class T>
inline std::shared_ptr<T> Object::GetComponent()
{
	for (auto component : components) {
		auto c = dynamic_pointer_cast<T>(component);
		if (c) {
			return c;
		}
	}
	return nullptr;
}
