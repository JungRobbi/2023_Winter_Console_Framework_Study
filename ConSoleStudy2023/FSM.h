#pragma once
#include "Object.h"

class FSM
{
public:
	FSM() {}
	virtual ~FSM() {}

	virtual void Update(double elapsedTime, Object* owner) = 0;
};

