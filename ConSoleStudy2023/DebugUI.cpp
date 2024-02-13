#include "DebugUI.h"
#include <windows.h>

DebugUI::DebugUI() : UI()
{
}

DebugUI::DebugUI(int x, int y) : UI(x, y)
{
}

DebugUI::DebugUI(int x, int y, int color) : UI(x, y, color)
{
}

DebugUI::~DebugUI()
{
}

void DebugUI::Start()
{
}

void DebugUI::Update(double elapsedTime)
{
}

void DebugUI::Render()
{
	UI::Render();

	string str;
	str += "  CURRENT SIZE  : " + to_string(CURRENT_MAP_SIZE.x) + ", " + to_string(CURRENT_MAP_SIZE.y);

	cout << str;
}