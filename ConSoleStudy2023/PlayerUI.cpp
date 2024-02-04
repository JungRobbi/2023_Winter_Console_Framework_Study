#include "PlayerUI.h"
#include "Player.h"

PlayerUI::PlayerUI() : UI(), object()
{
}

PlayerUI::PlayerUI(int x, int y) : UI(x, y), object()
{
}

PlayerUI::PlayerUI(int x, int y, int color) : UI(x, y, color), object()
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Start()
{
}

void PlayerUI::Update(double elapsedTime)
{
}

void PlayerUI::Render()
{
	UI::Render();
	if (nullptr == object)
		return;
	string str;
	str += "Pos: " + to_string(object->GetPos().x) + ", " + to_string(object->GetPos().y);
	str += "      ";
	cout << str;
}

void PlayerUI::SetPlayer(shared_ptr<Object> player)
{
	object = player;
}
