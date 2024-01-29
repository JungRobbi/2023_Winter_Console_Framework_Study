#pragma once
#include "Scene.h"
class LoginScene :
    public Scene
{
public:
	LoginScene();
	virtual ~LoginScene();

	virtual void Initialize();
	virtual void Update(double elapsedTime);
	virtual void Render();
};

