#pragma once
#include "FSMState.h"
#include <iostream>

class MonsterWanderState :
    public FSMState
{
public:
    void Enter(Object* owner)
    { 
        std::cout << "                 MonsterWanderState Enter!" << std::endl;
    }
    void Execute(Object* owner)
    {
        std::cout << "                 MonsterWanderState Execute!" << std::endl;
    }
    void Exit(Object* owner)
    { 
        std::cout << "                 MonsterWanderState Exit!" << std::endl;
    }
};