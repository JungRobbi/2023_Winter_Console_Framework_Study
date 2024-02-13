#pragma once
#include "UI.h"
class Object;
class DebugUI :
	public UI
{
public:
	DebugUI();
	DebugUI(int x, int y);
	DebugUI(int x, int y, int color);
	virtual ~DebugUI();

	virtual void Start() final;
	virtual void Update(double elapsedTime) final;
	virtual void Render() final;
};

