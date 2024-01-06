#include "stdafx.h"
#include "Input.h"
#include "Scene.h"
#include "Timer.h"

int main(int argc, char** argv)
{
	shared_ptr<Scene> scene = make_shared<Scene>();
	scene->Initialize();

	Timer::Initialize();
	Input::Initialize();
	
	while (true) {
		Timer::Update();
		Input::Update();
		scene->Update();
		scene->Render();

		cout << "                   PlayTime : " << Timer::GetPlayTimeHour() << " h  ";
		cout << Timer::GetPlayTimeMinute() << " m  ";
		cout << Timer::GetPlayTimeSeconds() << "\ts  " << endl;
	}
}