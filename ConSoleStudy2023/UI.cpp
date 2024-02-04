#include "UI.h"
#include <windows.h>

UI::UI() : uiPosition(), colorType(0)
{
}

UI::UI(int x, int y) : uiPosition(), colorType(0)
{
	uiPosition.x = x;
	uiPosition.y = y;
}

UI::UI(int x, int y, int color) : uiPosition(), colorType(color)
{
	uiPosition.x = x;
	uiPosition.y = y;
}

void UI::Start()
{
}

void UI::Update(double elapsedTime)
{
}

void UI::Render()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
		COORD{ static_cast<short>(uiPosition.x), static_cast<short>(uiPosition.y) });
	cout << "UI TEST!";
}
