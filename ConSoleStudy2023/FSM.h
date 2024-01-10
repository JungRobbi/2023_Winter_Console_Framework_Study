#pragma once
#include "Object.h"
#include "FSMState.h"

class FSM
{
protected:
	shared_ptr<FSMState> currentState;
	Object* owner;
public:
	FSM() : currentState(nullptr), owner(nullptr) {}
	FSM(Object* own) : owner(own) {}
	FSM(Object* own, shared_ptr<FSMState> startState) : owner(own), currentState(startState) 
	{
		currentState->Enter(owner);
	}
	virtual ~FSM() {}

	virtual void Update(double elapsedTime) 
	{ 
		currentState->Execute(owner);
	};

	virtual void ChangeState(shared_ptr<FSMState> newState)
	{
		currentState->Exit(owner);
		currentState = newState;
		currentState->Enter(owner);
	}
};

