#include "Scene.h"
#include "Input.h"
#include "Object.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	for (int i{}; i < 10; ++i) {
		scene.emplace_back();
		for (int j{}; j < 10; ++j) {
			if ((i + j) & 1) {
				scene[i].emplace_back(E_TILE);
			}
			else {
				scene[i].emplace_back(E_TILE + 1);
			}
		}
	}

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Scene::Update()
{
	/*for (int i{}; i < 10; ++i) {
		for (int j{}; j < 10; ++j) {
			if ((i + j) & 1) {
				scene[i][j] = E_TILE;
			}
			else {
				scene[i][j] = E_TILE + 1;
			}
		}
	}*/
}

void Scene::Render()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });

	string str{};


	for (int i{}; i < scene.size(); ++i) {
		for (int j{}; j < scene[i].size(); ++j) {
			
			switch (scene[i][j])
			{
			case E_TILE:
				str += "A ";
				break;
			case E_TILE + 1:
				str += "B ";
				break;
			default:
				str += "  ";
				break;
			}
		}
		str += '\n';
	}
	cout << str << endl;
}
