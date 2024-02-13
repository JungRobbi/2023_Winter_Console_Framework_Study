#include "stdafx.h"
#include "GameFramework.h"
#include "Input.h"
#include "Scene.h"
#include "Timer.h"

#include "NetworkMGR.h"
#include "UIMGR.h"

#include "LoginScene.h"
#include "LobbyScene.h"
#include "StageScene.h"
#include "../ServerLib/PacketQueue.h"

GameFramework& GameFramework::GetInstance()
{
	static GameFramework instance;
	return instance;
}

void GameFramework::Initialize()
{
	MapSize::CURRENT_MAP_SIZE = Vec2{ LOBBY_SIZE_X, LOBBY_SIZE_Y };

	auto& timer = Timer::GetInstance();
	auto& input = Input::GetInstance();
	timer.Initialize();
	input.Initialize();

	auto& animationMGR = AnimationMGR::GetInstance();
	animationMGR.Initialize();

	auto& networkMGR = NetworkMGR::GetInstance();
	networkMGR.Initialize();

	auto& packetQueue = PacketQueue::GetInstance();
	packetQueue.Initialize();

	auto& uiMGR = UIMGR::GetInstance();
	uiMGR.Initialize();

	CS_LOGIN_PACKET sendPacket;
	sendPacket.size = sizeof(CS_LOGIN_PACKET);
	sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_CS_LOGIN);
	packetQueue.AddSendPacket(&sendPacket);
}

void GameFramework::Run()
{
//	ChangeScene(E_SCENE::E_STAGE1);
	ChangeScene(E_SCENE::E_LOBBY);

	auto& timer = Timer::GetInstance();
	auto& input = Input::GetInstance();
	auto& networkMGR = NetworkMGR::GetInstance();
	auto& uiMGR = UIMGR::GetInstance();

	while (true) {
		networkMGR.Update();

		timer.Update();
		input.Update(timer.GetElapsedTimeSeconds());
		Scene::MainScene->Update(timer.GetElapsedTimeSeconds());
		Scene::MainScene->Render();
		uiMGR.Render();

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
	auto& uiMGR = UIMGR::GetInstance();
	uiMGR.Clear();

	switch (type)
	{
	case E_SCENE::E_LOGIN: {
		Scene::MainSceneShared = make_shared<LoginScene>();
		Scene::MainSceneShared->Initialize();
		break;
	}
	case E_SCENE::E_LOBBY: {
		MapSize::CURRENT_MAP_SIZE = Vec2{ LOBBY_SIZE_X , LOBBY_SIZE_Y };
		Scene::MainSceneShared = make_shared<LobbyScene>();
		Scene::MainSceneShared->Initialize();
		break;
	}
	case E_SCENE::E_STAGE1: {
		MapSize::CURRENT_MAP_SIZE = Vec2{ STAGE_SIZE_X , STAGE_SIZE_Y };
		Scene::MainSceneShared = make_shared<StageScene>();
		Scene::MainSceneShared->Initialize();
		break;
	}
	default:
		break;
	}
	Scene::MainScene = Scene::MainSceneShared.get();
}
