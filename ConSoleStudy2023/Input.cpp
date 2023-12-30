#include "Input.h"
#include <conio.h>

double Input::KeyInputTime;
double Input::MouseInputTime;
bool Input::keys[256];
bool Input::keyUp[256];
bool Input::keyDown[256];
bool Input::keysToggle[256];
bool Input::keysOnlyToggle[256];
bool Input::LMouse;
bool Input::RMouse;

void Input::Initialize()
{
	KeyClear();
	MouseClear();
}

void Input::Update()
{
	//KeyInputTime += 0.01; // ms 단위
	//MouseInputTime += 0.01;
	//
	//if (KeyInputTime > 10 * 1000) { // 10초 이상 누를 시 Clear
	//	KeyTimerReset();
	//}
	//
	//if (MouseInputTime > 10 * 1000) { // 10초 이상 누를 시 Clear
	//	MouseTimerReset();
	//}
	KeyClear();
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
