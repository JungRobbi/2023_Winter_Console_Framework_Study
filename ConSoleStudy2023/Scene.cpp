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
	Object_Shapes[E_OBJECT::E_WALL] = "♂";
	Object_Shapes[E_OBJECT::E_TILE] = "  ";
	Object_Shapes[E_OBJECT::E_TILE + 1] = "∴";
	Object_Shapes[E_OBJECT::E_TILE + 2] = "♂";
	Object_Shapes[E_OBJECT::E_TILE + 3] = "Α ";
	Object_Shapes[E_OBJECT::E_TILE + 4] = "Β ";
	Object_Shapes[E_OBJECT::E_TILE + 5] = "Λ ";
	Object_Shapes[E_OBJECT::E_TILE + 6] = "≤";
	Object_Shapes[E_OBJECT::E_EFFECT] = "ㄧ";
	Object_Shapes[E_OBJECT::E_EFFECT + 1] = "ㄨ";
	Object_Shapes[E_OBJECT::E_EFFECT + 2] = "ㄩ";
	Object_Shapes[E_OBJECT::E_EFFECT_ATTACK] = "∝";

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
		Object_Animation[E_OBJECT::E_EFFECT].emplace_back(E_OBJECT::E_EFFECT + 2);
		Object_Animation[E_OBJECT::E_EFFECT].emplace_back(E_OBJECT::E_EFFECT + 1);
		Object_Animation[E_OBJECT::E_EFFECT].emplace_back(E_OBJECT::E_EFFECT);
		Object_Animation[E_OBJECT::E_EFFECT].emplace_back(E_OBJECT::E_EFFECT_ATTACK);
	}
	{
		Object_Animation[E_OBJECT::E_EFFECT + 1].emplace_back(E_OBJECT::E_EFFECT_ATTACK);
	}

	
	//AddObject(Vec2{ StageSizeX / 2, StageSizeY / 2 }, E_OBJECT::E_CLIENT, my_id);

	objects[my_id] = make_shared<Player>(Vec2{ 5, 5 }, E_OBJECT::E_CLIENT, my_id);
	objects[my_id]->SetAnimationStateMAX(Object_Animation[E_OBJECT::E_CLIENT].size());
	objects[my_id]->SetSight(10);


	int num_monster{ 100 };
	for (int i{}; i < num_monster; ++i) {
		AddMonster(Vec2{ (int)(StageSizeX * rand_realUid(dre)), (int)(StageSizeY * rand_realUid(dre)) }, E_OBJECT::E_ENEMY);
	}

	for (int i{}; i < StageSizeY; ++i) {
		scene.emplace_back();
		for (int j{}; j < StageSizeX; ++j) {
			scene[i].emplace_back(E_TILE);
		}
	}

	for (int i{}; i < StageSizeY; ++i) {
		stage.emplace_back();
		for (int j{}; j < StageSizeX; ++j) {
			if (i == 0 || j == 0 || i == StageSizeY - 1 || j == StageSizeX - 1)
				stage[i].emplace_back(E_TILE + 1);
			else if (i % 10 == 9 && j % 10 == 9) 
				stage[i].emplace_back(E_TILE + 5);
			else if (j % 10 == 9) 
				stage[i].emplace_back(E_TILE + 4);
			else if (i % 10 == 9) 
				stage[i].emplace_back(E_TILE + 3);
			else 
				stage[i].emplace_back(E_TILE);
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
	//Collide 贸府
	///////
	for (auto& object : objects) {
		if (object.second->GetType() == E_OBJECT::E_ENEMY) {

			auto colliderList = CollideCheck(object.second->GetPos());
			for (auto collideId : colliderList) {
				if (collideId == object.second->GetId())
					continue;
				if (objects[collideId]->GetType() >= E_OBJECT::E_EFFECT) {
					if (E_OBJECT::E_EFFECT_ATTACK == Object_Animation[objects[collideId]->GetType()][objects[collideId]->GetAnimationState()]) {
						RemoveObject(object.second->GetId());
					}
				}
			}
		}
	}

	///////
	///////
	///////

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
		auto p = my_pos + my_dir;
		if (p.x >= 0 && p.x < StageSizeX &&
			p.y >= 0 && p.y < StageSizeY) {
			AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
		}

		if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
			global_effect_id = E_OBJECT::E_EFFECT;
		}
	}
	if (Input::keys['s']) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();
		auto p = my_pos + my_dir;
		if (p.x >= 0 && p.x < StageSizeX &&
			p.y >= 0 && p.y < StageSizeY) {
			AddSkill(p, E_OBJECT::E_EFFECT + 1, 5.f, 1.f);
		}

		if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
			global_effect_id = E_OBJECT::E_EFFECT;
		}
	}
	if (Input::keys['d']) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();
		{
			auto p = my_pos + my_dir + my_dir;
			if (p.x >= 0 && p.x < StageSizeX &&
				p.y >= 0 && p.y < StageSizeY) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_UP;
			if (p.x >= 0 && p.x < StageSizeX &&
				p.y >= 0 && p.y < StageSizeY) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_DOWN;
			if (p.x >= 0 && p.x < StageSizeX &&
				p.y >= 0 && p.y < StageSizeY) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_LEFT;
			if (p.x >= 0 && p.x < StageSizeX &&
				p.y >= 0 && p.y < StageSizeY) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_RIGHT;
			if (p.x >= 0 && p.x < StageSizeX &&
				p.y >= 0 && p.y < StageSizeY) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
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
	if (objects.end() != objects.find(my_id)) {
		objects[my_id]->Update(Timer::GetElapsedTimeSeconds());

		auto pos = objects[my_id]->GetPos();
		scene[pos.y][pos.x] = Object_Animation[objects[my_id]->GetType()][objects[my_id]->GetAnimationState()];
	}

	//Delete 贸府
	while (removeQueue.size()) {
		auto id = *removeQueue.begin();
		objects.erase(id);
		removeQueue.pop_front();
	}
}

void Scene::Render()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });

	string str{};

	if (nullptr == objects[my_id])
		return;

	auto sight = objects[my_id]->GetSight();
	for (int i{ objects[my_id]->GetPos().y - sight}; i < objects[my_id]->GetPos().y + sight; ++i) {
		for (int j{ objects[my_id]->GetPos().x - sight }; j < objects[my_id]->GetPos().x + sight; ++j) {
			if (i < 0 || j < 0 || i >= StageSizeY || j >= StageSizeX) {
				str += "  ";
			}
			else {
				str += Object_Shapes[scene[i][j]];
			}
		}
		str += '\n';
	}
	cout << str << endl;
}

void Scene::AddObject(Vec2 pos, int type)
{
	if (type == E_OBJECT::E_CLIENT) {
		auto object = make_shared<Player>(pos, type, global_id++);
		object->SetAnimationStateMAX(Object_Animation[type].size());
		createQueue.push_back(object);
	}
	else {
		auto object = make_shared<Object>(pos, global_id++);
		object->SetAnimationStateMAX(Object_Animation[type].size());
		createQueue.push_back(object);
	}
}

void Scene::AddMonster(Vec2 pos, int type)
{
	auto object = make_shared<Monster>(pos, type, global_id++);
	object->SetAnimationStateMAX(Object_Animation[type].size());
	//烙矫
	object->SetTarget(objects[my_id]);
	createQueue.push_back(object);
}

void Scene::AddSkill(Vec2 pos, int type, double holdingTime)
{
	auto object = make_shared<Skill>(pos, type, global_effect_id++, holdingTime);
	object->SetAnimationStateMAX(Object_Animation[type].size());
	createQueue.push_back(object);
}

void Scene::AddSkill(Vec2 pos, int type, float animateSpeed, double holdingTime)
{
	auto object = make_shared<Skill>(pos, type, global_effect_id++, holdingTime);
	object->SetAnimationStateMAX(Object_Animation[type].size());
	object->SetAnimationSpeed(animateSpeed);
	createQueue.push_back(object);
}

void Scene::RemoveObject(unsigned long long id)
{
	removeQueue.emplace_back(id);
}

vector<unsigned long long> Scene::CollideCheck(Vec2 position)
{
	vector<unsigned long long> v{};

	for (auto& object : objects) {
		if (object.second->GetPos() == position)
			v.emplace_back(object.second->GetId());
	}

	return v;
}