#pragma once
class Component
{
public:
	virtual void Start() = 0;
	virtual void Update(double elapsedTime) = 0;
};

