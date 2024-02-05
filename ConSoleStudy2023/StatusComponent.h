#pragma once
#include "Component.h"
class StatusComponent :
    public Component
{
	float HP = 100.f;
	float HPMAX = 100.f;
	float Defence = 1.f;
	int sight = 3;
public:
    void Start();
    void Update(double elapsedTime);

	int GetSight();
	void SetSight(int i);
};

