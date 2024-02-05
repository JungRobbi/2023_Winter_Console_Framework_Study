#include "PlayerMovementComponent.h"
#include "stdafx.h"
#include "Input.h"
#include "Object.h"

void PlayerMovementComponent::Start()
{
}

void PlayerMovementComponent::Update(double elapsedTime)
{
	auto& input = Input::GetInstance();
	if (input.GetKey(224)) { // ��/��/��/��
		Vec2 my_pos = object->GetPos();
		if (input.GetKey(72)) { // ��
			object->SetDirection(E_DIRECTION::E_UP);
			if (my_pos.y - 1 >= 0)
				object->Move(E_DIRECTION::E_UP, 1);
		}
		if (input.GetKey(80)) { // ��
			object->SetDirection(E_DIRECTION::E_DOWN);
			if (my_pos.y + 1 < CURRENT_MAP_SIZE.y)
				object->Move(E_DIRECTION::E_DOWN, 1);
		}
		if (input.GetKey(75)) { // ��
			object->SetDirection(E_DIRECTION::E_LEFT);
			if (my_pos.x - 1 >= 0)
				object->Move(E_DIRECTION::E_LEFT, 1);
		}
		if (input.GetKey(77)) { // ��
			object->SetDirection(E_DIRECTION::E_RIGHT);
			if (my_pos.x + 1 < CURRENT_MAP_SIZE.x)
				object->Move(E_DIRECTION::E_RIGHT, 1);
		}
	}
}

void PlayerMovementComponent::SetPlayer(std::shared_ptr<Object> player)
{
	object = player;
}
