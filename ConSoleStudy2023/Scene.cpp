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

#include "../ServerLib/PacketQueue.h"
#include "StatusComponent.h"
#include "ShootSkill.h"
#include "ShootMonster.h"

#include <string>
#include <vector>

unsigned long long Scene::global_id = 1;
unsigned long long Scene::global_effect_id = E_OBJECT::E_EFFECT;

Scene* Scene::MainScene{ nullptr };
shared_ptr<Scene> Scene::MainSceneShared{ nullptr };
E_SCENE Scene::toChangeScene { E_SCENE::E_NONE };
unsigned long long Scene::my_id{ 0 };
char Scene::inputSkill{ ' ' };
double Scene::skillTimer{ 0.0 };
double Scene::skillSpeed{ 1.0 };

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Scene::Update(double elapsedTime)
{
	for (auto& object : objects) {
		auto component = object.second->GetComponent<StatusComponent>();
		if (component) {
			if (0 <= component->GetHP())
				RemoveObject(object.second->GetId());
		}
	}

	ProcessNetworkRecv();
}

void Scene::Render()
{
}

void Scene::CreateObjects()
{
	//Create 贸府
	while (createQueue.size()) {
		auto value = *createQueue.begin();
		value->Start();
		objects[value->GetId()] = value;
		createQueue.pop_front();
	}
}

void Scene::DeleteObjects()
{
	//Delete 贸府
	while (removeQueue.size()) {
		auto id = *removeQueue.begin();
		objects.erase(id);
		removeQueue.pop_front();
	}
}

shared_ptr<Object> Scene::AddObject(Vec2 pos, int type)
{
	auto& animationMGR = AnimationMGR::GetInstance();

	if (type == E_OBJECT::E_CLIENT) {
		auto object = make_shared<Player>(pos, type, global_id++);
		object->AddComponent<MovementComponent>();
		auto component = object->AddComponent<AnimationComponent>();
		component->SetAnimationStateMAX(animationMGR.GetAnimationShape(type).size());
		createQueue.push_back(object);
		return object;
	}
	else {
		auto object = make_shared<Object>(pos, type, global_id++);
		auto component = object->AddComponent<AnimationComponent>();
		component->SetAnimationStateMAX(animationMGR.GetAnimationShape(type).size());
		createQueue.push_back(object);
		return object;
	}
}

shared_ptr<Object> Scene::AddMonster(Vec2 pos, int type)
{
	auto object = make_shared<Monster>(pos, type, global_id++);
	object->SetTarget(objects[my_id]);
	createQueue.push_back(object);
	return object;
}

shared_ptr<Object> Scene::AddShootMonster(Vec2 pos, int type)
{
	auto object = make_shared<ShootMonster>(pos, type, global_id++);
	object->SetTarget(objects[my_id]);
	createQueue.push_back(object);
	return object;
}

shared_ptr<Object> Scene::AddSkill(Vec2 pos, int type, float animateSpeed, double holdingTime)
{
	auto object = make_shared<Skill>(pos, type, global_effect_id++, holdingTime, animateSpeed);
	createQueue.push_back(object);
	return object;
}

shared_ptr<Object> Scene::AddShootSkill(Vec2 pos, int type, float animateSpeed, double holdingTime, E_DIRECTION dir = E_DIRECTION::E_RIGHT)
{
	auto object = make_shared<ShootSkill>(pos, type, global_effect_id++, holdingTime, animateSpeed);
	
	if (pos.x >= 0 && pos.x < MapSize::CURRENT_MAP_SIZE.x &&
		pos.y >= 0 && pos.y < MapSize::CURRENT_MAP_SIZE.y) {
		object->SetDirection(dir);
		createQueue.push_back(object);
	}
	else 
		return nullptr;
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
		if (nullptr == object.second)
			continue;

		if (object.second->GetPos() == position)
			v.emplace_back(object.second->GetId());
	}

	return v;
}

vector<unsigned long long> Scene::CollideCheckForType(Vec2 position)
{
	vector<unsigned long long> v{};

	for (auto& object : objects) {
		if (nullptr == object.second)
			continue;

		if (object.second->GetPos() == position)
			v.emplace_back(object.second->GetType());
	}

	return v;
}

void Scene::ProcessNetworkRecv()
{
	auto& packetQueue = PacketQueue::GetInstance();

	while (false == packetQueue.RecvQueue.empty()) {
		char* recv_buf = packetQueue.RecvQueue.front();

		ProcessPacket(recv_buf);

		packetQueue.PopRecvPacket();
	}
}

void Scene::ProcessPacket(char* p_Packet)
{
}

void InitTitle(std::vector<std::vector<int>>& map, const std::vector<std::wstring>& title, const Vec2& pos)
{
	int left{ pos.x - int(title[0].size()) / 2 };
	int right{ pos.x + int(title[0].size()) / 2 };
	int top{ pos.y - int(title.size()) / 2 };
	int bottom{ pos.y + int(title.size()) / 2 };

	if (left < 0) {
		left = 0;
		right = title[0].size();
	}
	else if (right >= MapSize::CURRENT_MAP_SIZE.x) {
		right = MapSize::CURRENT_MAP_SIZE.x - 1;
		left = right - title[0].size();
	}
	if (top < 0) {
		top = 0;
		bottom = title.size();
	}
	else if (bottom >= MapSize::CURRENT_MAP_SIZE.y) {
		bottom = MapSize::CURRENT_MAP_SIZE.y - 1;
		top = bottom - title.size();
	}

	for (int i{}; i < title.size(); ++i) {
		for (int j{}; j < title[i].size(); ++j) {
			wchar_t temp = title[i][j];
			if (0 == wcscmp(&temp, L"Γ"))
				map[top + i][left + j] = E_OBJECT::E_TILE + 7;
			else if (0 == wcscmp(&temp, L"Δ"))
				map[top + i][left + j] = E_OBJECT::E_TILE + 8;
			else if (0 == wcscmp(&temp, L"Ε"))
				map[top + i][left + j] = E_OBJECT::E_TILE + 9;
			else if (0 == wcscmp(&temp, L"Ζ"))
				map[top + i][left + j] = E_OBJECT::E_TILE + 10;
			else if (0 == wcscmp(&temp, L"Α"))
				map[top + i][left + j] = E_OBJECT::E_TILE + 3;
			else if (0 == wcscmp(&temp, L"Β"))
				map[top + i][left + j] = E_OBJECT::E_TILE + 4;
			else if (0 == wcscmp(&temp, L" "))
				map[top + i][left + j] = E_OBJECT::E_TILE;
			else
				map[top + i][left + j] = E_OBJECT::E_TILE + 2;
		}
	}
}
