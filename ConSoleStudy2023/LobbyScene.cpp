#include "LobbyScene.h"
#include "Input.h"
#include "Skill.h"
#include "Player.h"
#include "Timer.h"
#include "Monster.h"
#include "AnimationComponent.h"
#include "AttackComponent.h"
#include "MovementComponent.h"
#include "PlayerMovementComponent.h"

#include "GameFramework.h"

#include <windows.h>

LobbyScene::LobbyScene() : Scene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Initialize()
{
	auto& animationMGR = AnimationMGR::GetInstance();

	for (int i{}; i < LOBBY_SIZE_Y; ++i) {
		lobby.emplace_back();
		for (int j{}; j < LOBBY_SIZE_X; ++j) {
			if (i % 10 == 9 && j % 10 == 9)
				lobby[i].emplace_back(E_TILE + 5);
			else
				lobby[i].emplace_back(E_TILE);
		}
	}

	for (int i{}; i < LOBBY_SIZE_Y; ++i) {
		scene.emplace_back();
		for (int j{}; j < LOBBY_SIZE_X; ++j) {
			scene[i].emplace_back(E_TILE);
		}
	}

	{ // player 积己
		objects[my_id] = make_shared<Player>(Vec2{ 5, 5 }, E_OBJECT::E_CLIENT, my_id);
		objects[my_id]->AddComponent<PlayerMovementComponent>();
		auto component = objects[my_id]->AddComponent<AnimationComponent>();
		component->SetAnimationStateMAX(animationMGR.GetAnimationShape(E_OBJECT::E_CLIENT).size());
		component->SetAnimationSpeed(2.f);
		objects[my_id]->SetSight(10);
	}

	Scene::Initialize();
}

void LobbyScene::Update(double elapsedTime)
{
	auto& timer = Timer::GetInstance();
	auto& animationMGR = AnimationMGR::GetInstance();

	// 盔夯 stage 汗荤
	for (int i{}; i < lobby.size(); ++i) {
		for (int j{}; j < lobby[i].size(); ++j) {
			scene[i][j] = lobby[i][j];
		}
	}

	CreateObjects();

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
					if (E_OBJECT::E_EFFECT_ATTACK == animationMGR.GetAnimationShape(objects[collideId]->GetType())[objects[collideId]->GetComponent<AnimationComponent>()->GetAnimationState()]) {
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
			if (my_pos.y + 1 < LOBBY_SIZE_Y)
				objects[my_id]->Move(E_DIRECTION::E_DOWN, 1);
		}
		if (input.GetKey(75)) { // ＄
			objects[my_id]->SetDirection(E_DIRECTION::E_LEFT);
			if (my_pos.x - 1 >= 0)
				objects[my_id]->Move(E_DIRECTION::E_LEFT, 1);
		}
		if (input.GetKey(77)) { // ℃
			objects[my_id]->SetDirection(E_DIRECTION::E_RIGHT);
			if (my_pos.x + 1 < LOBBY_SIZE_X)
				objects[my_id]->Move(E_DIRECTION::E_RIGHT, 1);
		}
	}
	if (input.GetKey('a')) {
		Vec2 my_pos = objects[my_id]->GetPos();
		E_DIRECTION my_dir = objects[my_id]->GetDirection();
		auto p = my_pos + my_dir;
		if (p.x >= 0 && p.x < LOBBY_SIZE_X &&
			p.y >= 0 && p.y < LOBBY_SIZE_Y) {
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
		if (p.x >= 0 && p.x < LOBBY_SIZE_X &&
			p.y >= 0 && p.y < LOBBY_SIZE_Y) {
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
			if (p.x >= 0 && p.x < LOBBY_SIZE_X &&
				p.y >= 0 && p.y < LOBBY_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_UP;
			if (p.x >= 0 && p.x < LOBBY_SIZE_X &&
				p.y >= 0 && p.y < LOBBY_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_DOWN;
			if (p.x >= 0 && p.x < LOBBY_SIZE_X &&
				p.y >= 0 && p.y < LOBBY_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_LEFT;
			if (p.x >= 0 && p.x < LOBBY_SIZE_X &&
				p.y >= 0 && p.y < LOBBY_SIZE_Y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}
		}
		{
			auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_RIGHT;
			if (p.x >= 0 && p.x < LOBBY_SIZE_X &&
				p.y >= 0 && p.y < LOBBY_SIZE_Y) {
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
			scene[pos.y][pos.x] = animationMGR.GetAnimationShape(object.second->GetType())[ac->GetAnimationState()];
	}

	if (input.GetKey('1')) 
		toChangeScene = E_SCENE::E_LOBBY;
	if (input.GetKey('2')) 
		toChangeScene = E_SCENE::E_STAGE1;

	DeleteObjects();
}

void LobbyScene::Render()
{
	auto& animationMGR = AnimationMGR::GetInstance();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });

	string str{};

	if (nullptr == objects[my_id])
		return;

	auto sight = objects[my_id]->GetSight();
	for (int i{ objects[my_id]->GetPos().y - sight }; i < objects[my_id]->GetPos().y + sight; ++i) {
		for (int j{ objects[my_id]->GetPos().x - sight }; j < objects[my_id]->GetPos().x + sight; ++j) {
			if (i < 0 || j < 0 || i >= LOBBY_SIZE_Y || j >= LOBBY_SIZE_X) {
				str += "  ";
			}
			else {
				str += animationMGR.GetShape(scene[i][j]);
			}
		}
		str += '\n';
	}
	cout << str << endl;
}
