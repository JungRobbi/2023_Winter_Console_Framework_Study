#include "InventoryComponent.h"
#include <windows.h>

const int InventoryComponent::MAX_INVENTORY = 5;

void InventoryComponent::Start()
{
	for (int i{}; i < MAX_INVENTORY; ++i) {
		inventory[i] = ItemBundle{ -1, -1 };
	}
}

void InventoryComponent::Update(double elapsedTime)
{
	
	Vec2 uiPos{ 44, 22 };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		COORD{ short(uiPos.x), short(uiPos.y) });

	string str;

	str += " [INVENTORY]  "s + "\n"s;
	cout << str;
	for (auto item : inventory) {
		if (item.second.objectType == -1 || item.second.num < 1)
			continue;

		str = ""s;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
			COORD{ short(uiPos.x), short(uiPos.y + 1) });
		if (item.second.objectType == (int)E_OBJECT::E_ITEM + 1) {
			str += "HP Potion : ";
		}
		str += to_string(item.second.num);
		cout << str;
	}
}

void InventoryComponent::AddItem(int type)
{
	auto p = find_if(inventory.begin(), inventory.end(),
		[type](const auto& rhs) {
			return rhs.second.objectType == type;
		});
	if (p != inventory.end()) {
		if (p->second.num != -1)
			++p->second.num;
	}
	else {
		for (int i{}; i < MAX_INVENTORY; ++i) {
			if (inventory[i].num == -1) {
				inventory[i] = ItemBundle{ type, 1 };
				break;
			}
		}
	}

}
