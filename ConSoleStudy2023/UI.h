#pragma once
#include "stdafx.h"

class UI
{
protected:
	Vec2 position;


public:
	virtual void Start();
	virtual void Update(double elapsedTime);
};

