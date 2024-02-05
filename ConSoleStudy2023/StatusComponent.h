#pragma once
#include "Component.h"
class StatusComponent :
    public Component
{
	float HP;
	float HPMAX;
	float Defence;
	int sight;
public:
    void Start();
    void Update(double elapsedTime);

	float GetHP();
	float GetHPMAX();
	float GetDefence();

	int GetSight();
	void SetSight(int i);

	void HitDamage(float damage);
};

