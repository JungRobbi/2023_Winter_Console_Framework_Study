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
	cout << "Pos: " << object->GetPos().x << ", " << object->GetPos().y;
}

void PlayerUI::SetPlayer(shared_ptr<Object> player)
{
	object = player;
}
