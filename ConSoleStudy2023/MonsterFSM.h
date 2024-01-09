#pragma once
#include "FSM.h"
#include "Monster.h"

class MonsterFSM :
    public FSM
{ 
public:
    MonsterFSM() : FSM() {}
    virtual ~MonsterFSM() {}

    virtual void Update(double elapsedTime, Object* owner)
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
};

