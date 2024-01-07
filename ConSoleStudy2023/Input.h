#pragma once
#include "stdafx.h"

class Input
{
	static double KeyInputTime;
	static double MouseInputTime;
public:
	static bool keys[256];
	static bool keyUp[256];
	static bool keyDown[256];
	static bool keysToggle[256];
	static bool keysOnlyToggle[256];

	static bool LMouse;
	static bool RMouse;

public:
	static void Initialize();
	static void Update(double elapsedTime);

	static void KeyClear();
	static void KeyTimerReset();

	static void MouseClear();
	static void MouseTimerReset();
};