#include "stdafx.h"
#include "Input.h"
#include "Scene.h"
#include "Timer.h"

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