#include "stdafx.h"
#include "Input.h"
#include "Scene.h"

int main(int argc, char** argv)
{
	shared_ptr<Scene> scene = make_shared<Scene>();
	scene->Initialize();
	Input::Initialize();

	while (true) {
		Input::Update();

		scene->Update();
		scene->Render();
	}
}