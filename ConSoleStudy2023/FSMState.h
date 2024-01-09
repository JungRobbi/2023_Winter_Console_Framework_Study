#pragma once
#include "Object.h"

class FSMState
{
public:
	virtual void Enter(Object* owner) = 0;
	virtual void Update(Object* owner) = 0;
	virtual void Exit(Object* owner) = 0;
};