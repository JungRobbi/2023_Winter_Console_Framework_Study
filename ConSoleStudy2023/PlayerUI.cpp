#include "PlayerUI.h"
#include <windows.h>

#include "Player.h"
#include "StatusComponent.h"
#include "AttackComponent.h"

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
	str += "  Pos  :     (" + to_string(object->GetPos().x) + ", " + to_string(object->GetPos().y) + ")  \n";

	auto statusComponent = object->GetComponent<StatusComponent>();
	if (statusComponent) {
		statusComponent->GetSight();
		str += " SIGHT : " + to_string(statusComponent->GetSight()) + "  \n";
		str += "  H P  : " + to_string((int)statusComponent->GetHP()) + " / " + to_string((int)statusComponent->GetHPMAX()) + "  \n";
		str += "DEFENCE: " + to_string((int)statusComponent->GetDefence()) + "  \n";
	}
	auto attackComponent = object->GetComponent<AttackComponent>();
	if (attackComponent) {
		str += "  A D  : " + to_string(attackComponent->GetAttackDamage()) + "  \n";
	}
	cout << str;
}

void PlayerUI::SetPlayer(shared_ptr<Object> player)
{
	object = player;
}
