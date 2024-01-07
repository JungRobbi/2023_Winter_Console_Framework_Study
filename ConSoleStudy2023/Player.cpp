#include "Player.h"

Player::Player() : Object()
{
	objectType = E_OBJECT::E_CLIENT;
}

Player::Player(Vec2 Pos, int type, unsigned long long id) : Object(Pos, id)
{
	objectType = type;
}

Player::~Player()
{
}

void Player::Update(double elapsedTime)
{
	Object::Update(elapsedTime);
}
