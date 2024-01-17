#pragma once
#include "stdafx.h"

class Input
{
	double KeyInputTime;
	double MouseInputTime;

	bool keys[256];
	bool keyUp[256];
	bool keyDown[256];
	bool keysToggle[256];
	bool keysOnlyToggle[256];

	bool LMouse;
	bool RMouse;

private:
	Input() = default;
	Input(const Input&) = delete;
	Input& operator=(const Input&) = delete;
	Input(Input&&) = delete;
	Input& operator=(Input&&) = delete;
	~Input() = default;
public:
	static Input& GetInstance();

	void Initialize();
	void Update(double elapsedTime);

	void KeyClear();
	void KeyTimerReset();

	void MouseClear();
	void MouseTimerReset();

	bool GetKey(unsigned char key);
};