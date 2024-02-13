#pragma once
#include "Object.h"
#include "FSM.h"

class Monster
	: public Object
{
protected:
	E_FSM_STATE currentState; 
	E_FSM_STATE flag;

	shared_ptr<Object> target{ nullptr };
	shared_ptr<FSM> monsterFSM;
public:
	Monster();
	Monster(Vec2 Pos, int type, unsigned long long id);
	~Monster();

	virtual void Start();
	virtual void Update(double elapsedTime);

	shared_ptr<Object> GetTarget();
	void SetTarget(shared_ptr<Object> tar);

	void SetFSMState(E_FSM_STATE state);
};

double DistanceVec2(Vec2 a, Vec2 b);
