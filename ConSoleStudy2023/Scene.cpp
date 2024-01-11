#include "Scene.h"
#include "Input.h"
#include "Skill.h"
#include "Player.h"
#include "Timer.h"
#include "Monster.h"

unsigned long long Scene::global_id = 1;
unsigned long long Scene::global_effect_id = E_OBJECT::E_EFFECT;

Scene* Scene::MainScene = nullptr;

Scene::Scene() : my_id(0)
{
	MainScene = this;
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	Object_Shapes[E_OBJECT::E_CLIENT] = "≮";
	Object_Shapes[E_OBJECT::E_CLIENT + 1] = "≠";
	Object_Shapes[E_OBJECT::E_TILE] = "  ";
	Object_Shapes[E_OBJECT::E_TILE + 1] = "∴";
	Object_Shapes[E_OBJECT::E_TILE + 2] = "♂";
	Object_Shapes[E_OBJECT::E_TILE + 3] = "⒚";
	Object_Shapes[E_OBJECT::E_TILE + 4] = "⒘";
	Object_Shapes[E_OBJECT::E_TILE + 5] = "≥";
	Object_Shapes[E_OBJECT::E_TILE + 6] = "≤";
	Object_Shapes[E_OBJECT::E_EFFECT] = "∝";

	{
		Object_Animation[E_OBJECT::E_CLIENT].emplace_back(E_OBJECT::E_CLIENT);
		Object_Animation[E_OBJECT::E_CLIENT].emplace_back(E_OBJECT::E_CLIENT + 1);
	}
	{
		Object_Animation[E_OBJECT::E_ENEMY].emplace_back(E_OBJECT::E_CLIENT + 1);
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
	{
		Object_Animation[E_OBJECT::E_EFFECT + 1].emplace_back(E_OBJECT::E_EFFECT);
	}

	
	AddObject(Vec2{ StageSizeX / 2, StageSizeY / 2 }, E_OBJECT::E_CLIENT, my_id);

	AddMonster(Vec2{ 3, 3 }, E_OBJECT::E_ENEMY, global_id++);

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

void Scene::Update(double elapsedTime)
{
	//Create 贸府
	while (createQueue.size()) {
		auto value = *createQueue.begin();
		objects[value->GetId()] = value;
		createQueue.pop_front();
	}

	// 盔夯 stage 汗荤
	for (int i{}; i < stage.size(); ++i) {
		for (int j{}; j < stage[i].size(); ++j) {
			scene[i][j] = stage[i][j];
		}
	}

	///////
	//Input 贸府
	///////
	if (Input::keys[224]) { // ¤/￠/＄/℃
		Vec2 my_pos = objects[my_id]->GetPos();
		if (Input::keys[72]) { // ¤
			objects[my_id]->SetDirection(E_DIRECTION::E_UP);
			if (my_pos.y - 1 >= 0)
				objects[my_id]->Move(E_DIRECTION::E_UP, 1);
		}
		if (Input::keys[80]) { // ￠
			objects[my_id]->SetDirection(E_DIRECTION::E_DOWN);
			if (my_pos.y + 1 < StageSizeY)
				objects[my_id]->Move(E_DIRECTION::E_DOWN, 1);
		}
		if (Input::keys[75]) { // ＄
			objects[my_id]->SetDirection(E_DIRECTION::E_LEFT);
			if (my_pos.x - 1 >= 0)
				objects[my_id]->Move(E_DIRECTION::E_LEFT, 1);
		}
		if (Input::keys[77]) { // ℃
			objects[my_id]->SetDirection(E_DIRECTION::E_RIGHT);
			if (my_pos.x + 1 < StageSizeX)
				objects[my_id]->Move(E_DIRECTION::E_RIGHT, 1);
		}
	}
	if (Input::keys['a']) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();

		switch (my_dir)
		{
		case E_UP:
			AddSkill(Vec2{ my_pos.x, my_pos.y - 1 }, E_OBJECT::E_EFFECT, 8.f, 1.f, global_effect_id++);
			break;
		case E_DOWN:
			AddSkill(Vec2{ my_pos.x, my_pos.y + 1 }, E_OBJECT::E_EFFECT, 8.f, 1.f, global_effect_id++);
			break;
		case E_LEFT:
			AddSkill(Vec2{ my_pos.x - 1, my_pos.y }, E_OBJECT::E_EFFECT, 8.f, 1.f, global_effect_id++);
			break;
		case E_RIGHT:
			AddSkill(Vec2{ my_pos.x + 1, my_pos.y }, E_OBJECT::E_EFFECT, 8.f, 1.f, global_effect_id++);
			break;
		default:
			break;
		}

		if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
			global_effect_id = E_OBJECT::E_EFFECT;
		}
	}
	///////
	///////
	///////


	//Player 力寇 Update
	for (auto& object : objects) {
		if (nullptr == object.second || object.second->GetId() == my_id)
			continue;
		object.second->Update(Timer::GetElapsedTimeSeconds());
	}
	//Player 力寇 Render
	for (auto& object : objects) {
		if (nullptr == object.second || object.second->GetId() == my_id)
			continue;
		auto pos = object.second->GetPos();
		scene[pos.y][pos.x] = Object_Animation[object.second->GetType()][object.second->GetAnimationState()];
	}
	//Player Update, Render
	if (nullptr != objects[my_id]) {
		objects[my_id]->Update(Timer::GetElapsedTimeSeconds());

		auto pos = objects[my_id]->GetPos();
		scene[pos.y][pos.x] = Object_Animation[objects[my_id]->GetType()][objects[my_id]->GetAnimationState()];
	}

	//Delete 贸府
	while (removeQueue.size()) {
		auto id = *removeQueue.begin();
		objects[id] = nullptr;
		removeQueue.pop_front();
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

void Scene::AddObject(Vec2 pos, int type, unsigned long long id)
{
	if (type == E_OBJECT::E_CLIENT) {
		auto object = make_shared<Player>(pos, type, id);
		object->SetAnimationStateMAX(Object_Animation[type].size());
		createQueue.push_back(object);
	}
	else {
		auto object = make_shared<Object>(pos, id);
		object->SetAnimationStateMAX(Object_Animation[type].size());
		createQueue.push_back(object);
	}
}

void Scene::AddMonster(Vec2 pos, int type, unsigned long long id)
{
	auto object = make_shared<Monster>(pos, type, id);
	object->SetAnimationStateMAX(Object_Animation[type].size());
	//烙矫
	object->SetTarget(objects[my_id]);
	createQueue.push_back(object);
}

void Scene::AddSkill(Vec2 pos, int type, double holdingTime, unsigned long long id)
{
	auto object = make_shared<Skill>(pos, type, id, holdingTime);
	object->SetAnimationStateMAX(Object_Animation[type].size());
	createQueue.push_back(object);
}

void Scene::AddSkill(Vec2 pos, int type, float animateSpeed, double holdingTime, unsigned long long id)
{
	auto object = make_shared<Skill>(pos, type, id, holdingTime);
	object->SetAnimationStateMAX(Object_Animation[type].size());
	object->SetAnimationSpeed(animateSpeed);
	createQueue.push_back(object);
}

void Scene::RemoveObject(unsigned long long id)
{
	removeQueue.emplace_back(id);
}
