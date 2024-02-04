#pragma once
#include "UI.h"
class Object;
class PlayerUI :
    public UI
{
	shared_ptr<Object> object;
public:
	PlayerUI();
	PlayerUI(int x, int y);
	PlayerUI(int x, int y, int color);
	virtual ~PlayerUI();

	virtual void Start() final;
	virtual void Update(double elapsedTime) final;
	virtual void Render() final;

	void SetPlayer(shared_ptr<Object> player);
};

