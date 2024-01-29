#include "StageScene.h"

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
}

void StageScene::Initialize()
{
	for (int i{}; i < STAGE_SIZE_Y; ++i) {
		stage.emplace_back();
		for (int j{}; j < STAGE_SIZE_X; ++j) {
			if (i % 10 == 9 && j % 10 == 9)
				stage[i].emplace_back(E_TILE + 5);
			else if (j % 10 == 9)
				stage[i].emplace_back(E_TILE + 4);
			else if (i % 10 == 9)
				stage[i].emplace_back(E_TILE + 3);
			else
				stage[i].emplace_back(E_TILE);
		}
	}
}

void StageScene::Update(double elapsedTime)
{
}

void StageScene::Render()
{
}
