#pragma once
#include "stdafx.h"

class UI
{
protected:
	Vec2 uiPosition;
	int colorType;

public:
	UI();
	UI(int x, int y);
	UI(int x, int y, int color);
	virtual ~UI();

	virtual void Start();
	virtual void Update(double elapsedTime);
	virtual void Render();
};

