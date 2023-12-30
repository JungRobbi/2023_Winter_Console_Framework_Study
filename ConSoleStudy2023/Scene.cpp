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
			scene[i].emplace_back(E_TILE);
		}
	}

	for (int i{}; i < 10; ++i) {
		stage.emplace_back();
		for (int j{}; j < 10; ++j) {
			if ((i + j) & 1) {
				stage[i].emplace_back(E_TILE);
			}
			else {
				stage[i].emplace_back(E_TILE + 1);
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
	if (Input::keys[224]) { // ¡è/¡é/¡ç/¡æ
		Vec2 my_pos = objects[my_id]->GetPos();
		if (Input::keys[72]) { // ¡è
			if (my_pos.y - 1 > 0)
				objects[my_id]->SetPos(Vec2{ my_pos.x, my_pos.y - 1 });
		}
		if (Input::keys[80]) { // ¡é
			if (my_pos.y + 1 < StageSizeY)
				objects[my_id]->SetPos(Vec2{ my_pos.x, my_pos.y + 1 });
		}
		if (Input::keys[75]) { // ¡ç
			if (my_pos.x - 1 > 0)
				objects[my_id]->SetPos(Vec2{ my_pos.x - 1, my_pos.y });
		}
		if (Input::keys[77]) { // ¡æ
			if (my_pos.x + 1 < StageSizeX)
				objects[my_id]->SetPos(Vec2{ my_pos.x + 1, my_pos.y });
		}
	}

	for (int i{}; i < stage.size(); ++i) {
		for (int j{}; j < stage[i].size(); ++j) {
			scene[i][j] = stage[i][j];
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
				str += "¨Í";
				break;
			case E_OBJECT::E_TILE:
				str += "¡à";
				break;
			case E_OBJECT::E_TILE + 1:
				str += "¡á";
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
