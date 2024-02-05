#pragma once
#include "stdafx.h"
#include "Component.h"

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

	list<shared_ptr<Component>> components;
public:
	Object();
	Object(Vec2 Pos, unsigned long long id);
	Object(Vec2 Pos, int type, unsigned long long id);
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

	void Move(E_DIRECTION dir, int step);


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
