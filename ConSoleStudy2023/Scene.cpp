#include "Scene.h"
#include "Input.h"
#include "Skill.h"
#include "Player.h"

unsigned long long Scene::global_id = 1;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	Object_Shapes[E_OBJECT::E_CLIENT] = "★";
	Object_Shapes[E_OBJECT::E_CLIENT + 1] = "☆";
	Object_Shapes[E_OBJECT::E_TILE] = "  ";
	Object_Shapes[E_OBJECT::E_TILE + 1] = "□";
	Object_Shapes[E_OBJECT::E_TILE + 2] = "■";
	Object_Shapes[E_OBJECT::E_EFFECT] = "※";

	objects.emplace(my_id, make_shared<Player>(Vec2{ 0, 0 }, my_id));

	for (int i{}; i < 10; ++i) {
		scene.emplace_back();
		for (int j{}; j < 10; ++j) {
			scene[i].emplace_back(E_TILE);
		}
	}

	for (int i{}; i < 10; ++i) {
		stage.emplace_back();
		for (int j{}; j < 10; ++j) {
			if (i != 0 && j != 0 && i != 9 && j != 9) {
				stage[i].emplace_back(E_TILE);
			}
			else if ((i + j) & 1) {
				stage[i].emplace_back(E_TILE + 1);
			}
			else {
				stage[i].emplace_back(E_TILE + 2);
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
	// 원본 stage 복사
	for (int i{}; i < stage.size(); ++i) {
		for (int j{}; j < stage[i].size(); ++j) {
			scene[i][j] = stage[i][j];
		}
	}

	///////
	//Input 처리
	///////
	if (Input::keys[224]) { // ↑/↓/←/→
		Vec2 my_pos = objects[my_id]->GetPos();
		if (Input::keys[72]) { // ↑
			objects[my_id]->SetDirection(E_DIRECTION::E_UP);
			if (my_pos.y - 1 > 0)
				objects[my_id]->SetPos(Vec2{ my_pos.x, my_pos.y - 1 });
		}
		if (Input::keys[80]) { // ↓
			objects[my_id]->SetDirection(E_DIRECTION::E_DOWN);
			if (my_pos.y + 1 < StageSizeY)
				objects[my_id]->SetPos(Vec2{ my_pos.x, my_pos.y + 1 });
		}
		if (Input::keys[75]) { // ←
			objects[my_id]->SetDirection(E_DIRECTION::E_LEFT);
			if (my_pos.x - 1 > 0)
				objects[my_id]->SetPos(Vec2{ my_pos.x - 1, my_pos.y });
		}
		if (Input::keys[77]) { // →
			objects[my_id]->SetDirection(E_DIRECTION::E_RIGHT);
			if (my_pos.x + 1 < StageSizeX)
				objects[my_id]->SetPos(Vec2{ my_pos.x + 1, my_pos.y });
		}
	}
	if (Input::keys['a']) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();

		// createQueue 만들어야 함. (임시 상태)
		switch (my_dir)
		{
		case E_UP:
			objects.emplace(global_id + E_OBJECT::E_EFFECT, make_shared<Skill>(Vec2{ my_pos.x, my_pos.y - 1 }, global_id++ + E_OBJECT::E_EFFECT, 20.f));
			break;
		case E_DOWN:
			objects.emplace(global_id + E_OBJECT::E_EFFECT, make_shared<Skill>(Vec2{ my_pos.x, my_pos.y + 1 }, global_id++ + E_OBJECT::E_EFFECT, 20.f));
			break;
		case E_LEFT:
			objects.emplace(global_id + E_OBJECT::E_EFFECT, make_shared<Skill>(Vec2{ my_pos.x - 1, my_pos.y }, global_id++ + E_OBJECT::E_EFFECT, 20.f));
			break;
		case E_RIGHT:
			objects.emplace(global_id + E_OBJECT::E_EFFECT, make_shared<Skill>(Vec2{ my_pos.x + 1, my_pos.y }, global_id++ + E_OBJECT::E_EFFECT, 20.f));
			break;
		default:
			break;
		}
	}
	///////
	///////
	///////



	// removeQueue 만들어야 함. (임시 상태)
	vector<unsigned long long> toRemove;
	for (auto& object : objects) {
		if (object.second->GetRemoved()) {
			toRemove.emplace_back(object.first);
			continue;
		}

		if (object.second->GetId() == my_id)
			continue;

		object.second->Update();

		auto pos = object.second->GetPos();

		if (object.second->GetId() >= E_OBJECT::E_ENEMY) {
			scene[pos.y][pos.x] = E_OBJECT::E_EFFECT;
		}
	}
	{
		auto pos = objects[my_id]->GetPos();
		scene[pos.y][pos.x] = E_OBJECT::E_CLIENT;
	}

	for (int id : toRemove) {
		objects.erase(id);
	}
}

void Scene::Render()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });

	string str{};


	for (int i{}; i < scene.size(); ++i) {
		for (int j{}; j < scene[i].size(); ++j) {
			str += Object_Shapes[scene[i][j]];
		}
		str += '\n';
	}
	cout << str << endl;
}
