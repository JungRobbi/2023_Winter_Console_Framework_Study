#include "InventoryComponent.h"
#include <windows.h>

const int InventoryComponent::MAX_INVENTORY = 10;

void InventoryComponent::Start()
{
	for (int i{}; i < MAX_INVENTORY; ++i) {
		inventory[i] = ItemBundle{ -1, -1 };
	}
}

void InventoryComponent::Update(double elapsedTime)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		COORD{ 44, 22 });

	string str;
	str += " [INVENTORY]  "s + "\n"s;
	cout << str;
}

void InventoryComponent::AddItem(E_OBJECT type)
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
				inventory[i] = ItemBundle{ (int)type, 1 };
				break;
			}
		}
	}

}
