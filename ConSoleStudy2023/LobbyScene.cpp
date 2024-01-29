#include "LobbyScene.h"

LobbyScene::LobbyScene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Initialize()
{
	for (int i{}; i < LOBBY_SIZE_Y; ++i) {
		lobby.emplace_back();
		for (int j{}; j < LOBBY_SIZE_X; ++j) {
			if (i % 10 == 9 && j % 10 == 9)
				lobby[i].emplace_back(E_TILE + 5);
			else
				lobby[i].emplace_back(E_TILE);
		}
	}
}

void LobbyScene::Update(double elapsedTime)
{
}

void LobbyScene::Render()
{
}
