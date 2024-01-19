#include "Scene.h"
#include "Input.h"
#include "Skill.h"
#include "Player.h"
#include "Timer.h"
#include "Monster.h"
#include "AnimationComponent.h"
#include "AttackComponent.h"
#include "MovementComponent.h"
#include "PlayerMovementComponent.h"

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
	animationMGR = &AnimationMGR::GetInstance();
	animationMGR->Initialize();
	
	{ // player 积己
		objects[my_id] = make_shared<Player>(Vec2{ 5, 5 }, E_OBJECT::E_CLIENT, my_id);
		objects[my_id]->AddComponent<PlayerMovementComponent>();
		auto component = objects[my_id]->AddComponent<AnimationComponent>();
		component->SetAnimationStateMAX(animationMGR->GetAnimationShape(E_OBJECT::E_CLIENT).size());
		component->SetAnimationSpeed(2.f);
		objects[my_id]->SetSight(10);
	}

	int num_monster{ 100 };
	for (int i{}; i < num_monster; ++i) {
		AddMonster(Vec2{ (int)((STAGE_SIZE_X - 2) * rand_realUid(dre)) + 1, (int)((STAGE_SIZE_Y - 2) * rand_realUid(dre)) + 1 }, E_OBJECT::E_ENEMY);
	}

	for (int i{}; i < STAGE_SIZE_Y; ++i) {
		for (int j{}; j < STAGE_SIZE_X; ++j) {
			if (i == 0 || j == 0 || i == STAGE_SIZE_Y - 1 || j == STAGE_SIZE_X - 1)
				AddObject(Vec2{ j, i }, E_OBJECT::E_WALL);
		}
	}

	for (int i{}; i < STAGE_SIZE_Y; ++i) {
		scene.emplace_back();
		for (int j{}; j < STAGE_SIZE_X; ++j) {
			scene[i].emplace_back(E_TILE);
		}
	}

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

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Scene::Update(double elapsedTime)
{
	auto& timer = Timer::GetInstance();
	//Create 贸府
	while (createQueue.size()) {
		auto value = *createQueue.begin();
		value->Start();
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
					if (E_OBJECT::E_EFFECT_ATTACK == animationMGR->GetAnimationShape(objects[collideId]->GetType())[objects[collideId]->GetComponent<AnimationComponent>()->GetAnimationState()]) {
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
	auto& input = Input::GetInstance();
	if (input.GetKey(224)) { // ¤/￠/＄/℃
		Vec2 my_pos = objects[my_id]->GetPos();
		if (input.GetKey(72)) { // ¤
			objects[my_id]->SetDirection(E_DIRECTION::E_UP);
			if (my_pos.y - 1 >= 0)
				objects[my_id]->Move(E_DIRECTION::E_UP, 1);
		}
		if (input.GetKey(80)) { // ￠
			objects[my_id]->SetDirection(E_DIRECTION::E_DOWN);
			if (my_pos.y + 1 < STAGE_SIZE_Y)
				objects[my_id]->Move(E_DIRECTION::E_DOWN, 1);
		}
		if (input.GetKey(75)) { // ＄
			objects[my_id]->SetDirection(E_DIRECTION::E_LEFT);
			if (my_pos.x - 1 >= 0)
				objects[my_id]->Move(E_DIRECTION::E_LEFT, 1);
		}
		if (input.GetKey(77)) { // ℃
			objects[my_id]->SetDirection(E_DIRECTION::E_RIGHT);
			if (my_pos.x + 1 < STAGE_SIZE_X)
				objects[my_id]->Move(E_DIRECTION::E_RIGHT, 1);
		}
	}
	if (input.GetKey('a')) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();
		auto p = my_pos + my_dir;
		if (p.x >= 0 && p.x < STAGE_SIZE_X &&
			p.y >= 0 && p.y < STAGE_SIZE_Y) {
			AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
		}

		if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
			global_effect_id = E_OBJECT::E_EFFECT;
		}
	}
	if (input.GetKey('s')) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();
		auto p = my_pos + my_dir;
		if (p.x >= 0 && p.x < STAGE_SIZE_X &&
			p.y >= 0 && p.y < STAGE_SIZE_Y) {
			AddSkill(p, E_OBJECT::E_EFFECT + 1, 5.f, 1.f);
		}

		if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
			global_effect_id = E_OBJECT::E_EFFECT;
		}
	}
	if (input.GetKey('d')) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();
		{
			auto p = my_pos + my_dir + my_dir;
			if (p.x >= 0 && p.x < STAGE_SIZE_X &&
				p.y >= 0 && p.y < STAGE_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_UP;
			if (p.x >= 0 && p.x < STAGE_SIZE_X &&
				p.y >= 0 && p.y < STAGE_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_DOWN;
			if (p.x >= 0 && p.x < STAGE_SIZE_X &&
				p.y >= 0 && p.y < STAGE_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_LEFT;
			if (p.x >= 0 && p.x < STAGE_SIZE_X &&
				p.y >= 0 && p.y < STAGE_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_RIGHT;
			if (p.x >= 0 && p.x < STAGE_SIZE_X &&
				p.y >= 0 && p.y < STAGE_SIZE_Y) {
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


	//Update
	for (auto& object : objects) {
		if (nullptr == object.second)
			continue;
		object.second->Update(timer.GetElapsedTimeSeconds());
	}

	//Render
	for (auto& object : objects) {
		if (nullptr == object.second)
			continue;
		auto pos = object.second->GetPos();
		auto ac = object.second->GetComponent<AnimationComponent>();
		if (ac)
			scene[pos.y][pos.x] = animationMGR->GetAnimationShape(object.second->GetType())[ac->GetAnimationState()];
	}

	input.KeyClear();

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
			if (i < 0 || j < 0 || i >= STAGE_SIZE_Y || j >= STAGE_SIZE_X) {
				str += "  ";
			}
			else {
				str += animationMGR->GetShape(scene[i][j]);
			}
		}
		str += '\n';
	}
	cout << str << endl;
}

shared_ptr<Object> Scene::AddObject(Vec2 pos, int type)
{
	if (type == E_OBJECT::E_CLIENT) {
		auto object = make_shared<Player>(pos, type, global_id++);
		object->AddComponent<MovementComponent>();
		auto component = object->AddComponent<AnimationComponent>();
		component->SetAnimationStateMAX(animationMGR->GetAnimationShape(type).size());
		createQueue.push_back(object);
		return object;
	}
	else {
		auto object = make_shared<Object>(pos, type, global_id++);
		auto component = object->AddComponent<AnimationComponent>();
		component->SetAnimationStateMAX(animationMGR->GetAnimationShape(type).size());
		createQueue.push_back(object);
		return object;
	}
}

shared_ptr<Object> Scene::AddMonster(Vec2 pos, int type)
{
	auto object = make_shared<Monster>(pos, type, global_id++);
	object->AddComponent<MovementComponent>();
	auto component = object->AddComponent<AnimationComponent>();
	component->SetAnimationStateMAX(animationMGR->GetAnimationShape(type).size());
	//烙矫
	object->SetTarget(objects[my_id]);
	createQueue.push_back(object);
	return object;
}

shared_ptr<Object> Scene::AddSkill(Vec2 pos, int type, double holdingTime)
{
	auto object = make_shared<Skill>(pos, type, global_effect_id++, holdingTime);
	auto component = object->AddComponent<AnimationComponent>();
	component->SetAnimationStateMAX(animationMGR->GetAnimationShape(type).size());
	createQueue.push_back(object);
	return object;
}

shared_ptr<Object> Scene::AddSkill(Vec2 pos, int type, float animateSpeed, double holdingTime)
{
	auto object = make_shared<Skill>(pos, type, global_effect_id++, holdingTime);
	auto component = object->AddComponent<AnimationComponent>();
	component->SetAnimationStateMAX(animationMGR->GetAnimationShape(type).size());
	component->SetAnimationSpeed(animateSpeed);
	createQueue.push_back(object);
	return object;
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