#pragma once
#include "Object.h"

enum class E_FSM_STATE {
	E_FSM_WANDER, E_FSM_TRACKING, E_FSM_ATTACK
};

class FSMState
{
public:
	virtual void Enter(Object* owner) = 0;
	virtual void Execute(Object* owner) = 0;
	virtual void Exit(Object* owner) = 0;
};