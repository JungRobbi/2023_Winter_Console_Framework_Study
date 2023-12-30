#include "Scene.h"
#include "Input.h"

unsigned long long Scene::global_id = 1;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	objects.emplace(my_id, make_shared<Object>(Vec2{ 0, 0 }, my_id));

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
	if (Input::keys[224]) { // ก่/ก้/ก็/กๆ
		if (Input::keys[72]) { // ก่

		}
		if (Input::keys[80]) { // ก้

		}
		if (Input::keys[75]) { // ก็

		}
		if (Input::keys[77]) { // กๆ

		}
	}

	for (auto& object : objects) {
		auto pos = object.second->GetPos();
		scene[pos.y][pos.x] = E_OBJECT::E_CLIENT;
	}
}

void Scene::Render()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });

	string str{};


	for (int i{}; i < scene.size(); ++i) {
		for (int j{}; j < scene[i].size(); ++j) {
			
			switch (scene[i][j])
			{
			case E_OBJECT::E_CLIENT:
				str += "C ";
				break;
			case E_OBJECT::E_TILE:
				str += "A ";
				break;
			case E_OBJECT::E_TILE + 1:
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
