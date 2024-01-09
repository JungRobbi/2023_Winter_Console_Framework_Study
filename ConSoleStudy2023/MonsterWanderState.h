#pragma once
#include "FSMState.h"
#include "Monster.h"
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
		if (dynamic_cast<Monster*>(owner)) {
			if (owner->GetMoveable()) {
				owner->SetMoveable(false);
				owner->SetMoveTimer(0.0);

				E_DIRECTION dir = (E_DIRECTION)(rand_dirUid(dre));
				auto owner_pos = owner->GetPos();
				switch (dir)
				{
				case E_UP:
					if (owner_pos.y - 1 < 0)
						return;
					break;
				case E_DOWN:
					if (owner_pos.y + 1 >= StageSizeY)
						return;
					break;
				case E_LEFT:
					if (owner_pos.x - 1 < 0)
						return;
					break;
				case E_RIGHT:
					if (owner_pos.x + 1 >= StageSizeX)
						return;
					break;
				default:
					break;
				}

				owner->Move(dir, 1);
			}
		}
    }
    void Exit(Object* owner)
    { 
        std::cout << "                 MonsterWanderState Exit!" << std::endl;
    }
};