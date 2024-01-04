#include "Scene.h"
#include "Input.h"
#include "Skill.h"
#include "Player.h"

unsigned long long Scene::global_id = 1;
unsigned long long Scene::global_effect_id = E_OBJECT::E_EFFECT;

Scene::Scene() : my_id(0)
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
	Object_Shapes[E_OBJECT::E_TILE + 3] = "▣";
	Object_Shapes[E_OBJECT::E_TILE + 4] = "⊙";
	Object_Shapes[E_OBJECT::E_TILE + 5] = "◎";
	Object_Shapes[E_OBJECT::E_TILE + 6] = "●";
	Object_Shapes[E_OBJECT::E_EFFECT] = "※";

	{
		Object_Animation[E_OBJECT::E_CLIENT].emplace_back(E_OBJECT::E_CLIENT);
		Object_Animation[E_OBJECT::E_CLIENT].emplace_back(E_OBJECT::E_CLIENT + 1);
	}	
	{
		Object_Animation[E_OBJECT::E_TILE].emplace_back(E_OBJECT::E_TILE);
	}	
	{
		Object_Animation[E_OBJECT::E_TILE + 1].emplace_back(E_OBJECT::E_TILE + 1);
	}	
	{
		Object_Animation[E_OBJECT::E_TILE + 2].emplace_back(E_OBJECT::E_TILE + 2);
	}
	{
		Object_Animation[E_OBJECT::E_EFFECT].emplace_back(E_OBJECT::E_TILE + 3);
		Object_Animation[E_OBJECT::E_EFFECT].emplace_back(E_OBJECT::E_TILE + 2);
		Object_Animation[E_OBJECT::E_EFFECT].emplace_back(E_OBJECT::E_EFFECT);
	}

	auto player = make_shared<Player>(Vec2{ StageSizeX / 2, StageSizeY / 2 }, E_OBJECT::E_CLIENT, my_id);
	player->SetAnimationStateMAX(Object_Animation[E_OBJECT::E_CLIENT].size());
	objects[my_id] = player;

	for (int i{}; i < StageSizeY; ++i) {
		scene.emplace_back();
		for (int j{}; j < StageSizeX; ++j) {
			scene[i].emplace_back(E_TILE);
		}
	}

	for (int i{}; i < StageSizeY; ++i) {
		stage.emplace_back();
		for (int j{}; j < StageSizeX; ++j) {
			if (i != 0 && j != 0 && i != StageSizeY - 1 && j != StageSizeX - 1) {
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
		auto attack = make_shared<Skill>(Vec2{ my_pos.x, my_pos.y }, E_OBJECT::E_EFFECT, global_effect_id, EFFECT_MAX);
		attack->SetAnimationStateMAX(Object_Animation[E_OBJECT::E_EFFECT].size());
		switch (my_dir)
		{
		case E_UP:
			attack->SetPos(Vec2{ my_pos.x, my_pos.y - 1 });
			break;
		case E_DOWN:
			attack->SetPos(Vec2{ my_pos.x, my_pos.y + 1 });
			break;
		case E_LEFT:
			attack->SetPos(Vec2{ my_pos.x - 1, my_pos.y });
			break;
		case E_RIGHT:
			attack->SetPos(Vec2{ my_pos.x + 1, my_pos.y });
			break;
		default:
			break;
		}
		objects[global_effect_id++] = attack;

		if (global_effect_id > E_OBJECT::E_EFFECT + 50) {
			global_effect_id = E_OBJECT::E_EFFECT;
		}
	}
	///////
	///////
	///////



	// removeQueue 만들어야 함. (임시 상태)
	vector<unsigned long long> toRemove;
	for (auto& object : objects) {
		if (nullptr == object.second || object.second->GetId() == my_id)
			continue;

		if (object.second->GetRemoved()) {
			toRemove.emplace_back(object.first);
			continue;
		}

		object.second->Update();

		auto pos = object.second->GetPos();
		scene[pos.y][pos.x] = Object_Animation[object.second->GetType()][object.second->GetAnimationState()];
	}
	if (nullptr != objects[my_id]) {
		objects[my_id]->Update();

		auto pos = objects[my_id]->GetPos();
		scene[pos.y][pos.x] = Object_Animation[objects[my_id]->GetType()][objects[my_id]->GetAnimationState()];
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
