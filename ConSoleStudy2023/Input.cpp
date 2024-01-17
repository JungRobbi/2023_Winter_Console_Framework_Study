#include "stdafx.h"
#include "Input.h"
#include <conio.h>

Input& Input::GetInstance()
{
	static Input instance;
	return instance;
}

void Input::Initialize()
{
	KeyClear();
	MouseClear();
}

void Input::Update(double elapsedTime)
{
	//KeyInputTime += 0.01; // ms ����
	//MouseInputTime += 0.01;
	//
	//if (KeyInputTime > 10 * 1000) { // 10�� �̻� ���� �� Clear
	//	KeyTimerReset();
	//}
	//
	//if (MouseInputTime > 10 * 1000) { // 10�� �̻� ���� �� Clear
	//	MouseTimerReset();
	//}
	static int prevKey = 80;

	if (_kbhit()) {
		int currentKey = _getch();
		keys[currentKey] = true;
		if (prevKey == 224)
			keys[prevKey] = true;
		prevKey = currentKey;
	}
}

void Input::KeyClear()
{
	KeyInputTime = 0.f;
	memset(keys, 0, 256);
	memset(keyUp, 0, 256);
	memset(keyDown, 0, 256);
	memset(keysToggle, 0, 256);
	memset(keysOnlyToggle, 0, 256);
}

void Input::KeyTimerReset()
{
	KeyInputTime = 0.f;
}

void Input::MouseClear()
{
	MouseInputTime = 0.f;
	LMouse = false;
	RMouse = false;
}

void Input::MouseTimerReset()
{
	MouseInputTime = 0.f;
}

bool Input::GetKey(unsigned char key)
{
	return keys[key];
}