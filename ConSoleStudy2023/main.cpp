#include "stdafx.h"
#include "Input.h"
#include "Scene.h"
#include "Timer.h"

void ChangeScene(E_SCENE type);

int main(int argc, char** argv)
{
	shared_ptr<Scene> scene = make_shared<Scene>();
	scene->Initialize();

	auto& timer = Timer::GetInstance();
	auto& input = Input::GetInstance();
	timer.Initialize();
	input.Initialize();
	
	while (true) {
		timer.Update();
		input.Update(timer.GetElapsedTimeSeconds());
		scene->Update(timer.GetElapsedTimeSeconds());
		scene->Render();

		timer.RenderTimer();
	}
}

void ChangeScene(E_SCENE type)
{
	switch (type)
	{
	case E_SCENE::E_LOGIN:
		break;
	case E_SCENE::E_LOBBY:
		break;
	case E_SCENE::E_STAGE1:
		break;
	default:
		break;
	}
}