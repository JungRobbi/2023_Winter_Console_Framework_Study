#include "stdafx.h"
#include "GameFramework.h"
#include "Input.h"
#include "Scene.h"
#include "Timer.h"

#include "NetworkMGR.h"

#include "LoginScene.h"
#include "LobbyScene.h"
#include "StageScene.h"

GameFramework& GameFramework::GetInstance()
{
	static GameFramework instance;
	return instance;
}

void GameFramework::Initialize()
{
	auto& timer = Timer::GetInstance();
	auto& input = Input::GetInstance();
	timer.Initialize();
	input.Initialize();

	auto& animationMGR = AnimationMGR::GetInstance();
	animationMGR.Initialize();

	auto& networkMGR = NetworkMGR::GetInstance();
	networkMGR.Initialize();
}

void GameFramework::Run()
{
//	ChangeScene(E_SCENE::E_STAGE1);
	ChangeScene(E_SCENE::E_LOBBY);

	Initialize();
	auto& timer = Timer::GetInstance();
	auto& input = Input::GetInstance();
	auto& networkMGR = NetworkMGR::GetInstance();
	while (true) {
		networkMGR.Update();

		timer.Update();
		input.Update(timer.GetElapsedTimeSeconds());
		Scene::MainScene->Update(timer.GetElapsedTimeSeconds());
		Scene::MainScene->Render();


		timer.RenderTimer();			                     
		input.KeyClear();

		if (Scene::MainScene->toChangeScene != E_SCENE::E_NONE) {
			ChangeScene(Scene::MainScene->toChangeScene);
			Scene::MainScene->toChangeScene = E_SCENE::E_NONE;
		}
	}
}

void GameFramework::Destroy()
{
}

void GameFramework::ChangeScene(E_SCENE type)
{
	switch (type)
	{
	case E_SCENE::E_LOGIN: {
		Scene::MainSceneShared = make_shared<LoginScene>();
		Scene::MainSceneShared->Initialize();
		break;
	}
	case E_SCENE::E_LOBBY: {
		Scene::MainSceneShared = make_shared<LobbyScene>();
		Scene::MainSceneShared->Initialize();
		break;
	}
	case E_SCENE::E_STAGE1: {
		Scene::MainSceneShared = make_shared<StageScene>();
		Scene::MainSceneShared->Initialize();
		break;
	}
	default:
		break;
	}
	Scene::MainScene = Scene::MainSceneShared.get();
}
