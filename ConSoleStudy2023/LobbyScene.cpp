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
#include "NetworkMGR.h"
#include "UIMGR.h"

#include "../ServerLib/PacketQueue.h"
#include "PlayerUI.h"
#include "StatusComponent.h"
#include "ShootSkill.h"
#include "DebugUI.h"


LobbyScene::LobbyScene() : Scene()
{
}

LobbyScene::~LobbyScene()
{
}

void LobbyScene::Initialize()
{
	auto& animationMGR = AnimationMGR::GetInstance();
	auto& networkMGR = NetworkMGR::GetInstance();
	auto& packetQueue = PacketQueue::GetInstance();
	auto& uiMGR = UIMGR::GetInstance();

	{
		auto ui = uiMGR.AddUI<DebugUI>(21, 10);
	}

	/*

	┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┐
	│   ■■■   ■  ■  ■■■■   ■■■   ■■   ■■■■  ■■■■   │
	│   ■  ■  ■  ■  ■  ■  ■     ■  ■  ■     ■  ■   │
	│   ■  ■  ■  ■  ■  ■  ■ ■■  ■  ■  ■■■   ■  ■   │
	│   ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■     ■  ■   │
	│   ■■■    ■■   ■  ■   ■■■   ■■   ■■■■  ■  ■   │
	└ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┘

	┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┐
	│    ■■■  ■■■■   ■■   ■■■   ■■■■   │
	│   ■      ■■   ■  ■  ■  ■  ■      │
	│    ■■    ■■   ■  ■  ■■■   ■■■    │
	│      ■   ■■   ■  ■  ■ ■   ■      │
	│   ■■■    ■■    ■■   ■  ■  ■■■■   │
	└ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┘

	*/

	dungeonTitle = vector<string>{
	"┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┐",
	"│   ■■■   ■  ■  ■■■■   ■■■   ■■   ■■■■  ■■■■   │",
	"│   ■  ■  ■  ■  ■  ■  ■     ■  ■  ■     ■  ■   │",
	"│   ■  ■  ■  ■  ■  ■  ■ ■■  ■  ■  ■■■   ■  ■   │",
	"│   ■  ■  ■  ■  ■  ■  ■  ■  ■  ■  ■     ■  ■   │",
	"│   ■■■    ■■   ■  ■   ■■■   ■■   ■■■■  ■  ■   │",
	"└ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┘"
	};

	storeTitle = vector<string>{
	"┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┐",
	"│    ■■■  ■■■■   ■■   ■■■   ■■■■   │",
	"│   ■      ■■   ■  ■  ■  ■  ■      │",
	"│    ■■    ■■   ■  ■  ■■■   ■■■    │",
	"│      ■   ■■   ■  ■  ■ ■   ■      │",
	"│   ■■■    ■■    ■■   ■  ■  ■■■■   │",
	"└ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─┘"
	};

	storeTitle = vector<string>{
	"┌ ─ ┐",
	"│  ■│"
	"└  ─┘"
	};

	dungeonPos = Vec2{ 20, 10 };
	storePos = Vec2{ 20, 50 };

	lobby.clear();
	for (int i{}; i < MapSize::CURRENT_MAP_SIZE.y; ++i) {
		lobby.emplace_back();
		for (int j{}; j < MapSize::CURRENT_MAP_SIZE.x; ++j) {
			if ((i + 5) % 10 == 9 && (j + 5) % 10 == 9)
				lobby[i].emplace_back(E_TILE + 5);
			else
				lobby[i].emplace_back(E_TILE);
		}
	}
	
	storePos;
	for (int i{}; i < storeTitle.size(); ++i) {
		for (int j{}; j < storeTitle[i].size(); ++j) {

		}
	}
//	lobby[][];

	

	scene.clear();
	for (int i{}; i < MapSize::CURRENT_MAP_SIZE.y; ++i) {
		scene.emplace_back();
		for (int j{}; j < MapSize::CURRENT_MAP_SIZE.x; ++j) {
			scene[i].emplace_back(E_TILE);
		}
	}

	if (false == networkMGR.b_isNet) { // Network X
		{ // player 생성
			auto object = make_shared<Player>(Vec2{ 5, 5 }, E_OBJECT::E_CLIENT, my_id);
			object->Start();
			objects[my_id] = object;

			auto ui = uiMGR.AddUI<PlayerUI>(0, 21);
			ui->SetPlayer(object);
		}
	}
	else { // Network O
		CS_TO_LOBBY_PACKET sendPacket;
		sendPacket.size = sizeof(CS_TO_LOBBY_PACKET);
		sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_CS_TO_LOBBY);
		packetQueue.AddSendPacket(&sendPacket);
	}

	Scene::Initialize();
}

void LobbyScene::Update(double elapsedTime)
{
	auto& timer = Timer::GetInstance();
	auto& animationMGR = AnimationMGR::GetInstance();
	auto& networkMGR = NetworkMGR::GetInstance();
	auto& packetQueue = PacketQueue::GetInstance();

	// 원본 stage 복사
	for (int i{}; i < lobby.size(); ++i) {
		for (int j{}; j < lobby[i].size(); ++j) {
			scene[i][j] = lobby[i][j];
		}
	}

	CreateObjects();

	///////
	//Collide 처리
	///////
	for (auto& object : objects) {
		if (nullptr == object.second)
			continue;

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
	//Input 처리
	///////
	auto& input = Input::GetInstance();

	if (false == networkMGR.b_isNet) {
		if (input.GetKey('a')) {
			Vec2 my_pos = objects[my_id]->GetPos();
			E_DIRECTION my_dir = objects[my_id]->GetDirection();
			auto p = my_pos + my_dir;
			if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
				p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
				AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
			}

			if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
				global_effect_id = E_OBJECT::E_EFFECT;
			}
		}
		if (input.GetKey('s')) {
			Vec2 my_pos = objects[my_id]->GetPos();
			E_DIRECTION my_dir = objects[my_id]->GetDirection();
			{
				auto p = my_pos + my_dir + my_dir;
				if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
					p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
					AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
				}
			}
			{
				auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_UP;
				if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
					p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
					AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
				}
			}
			{
				auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_DOWN;
				if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
					p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
					AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
				}
			}
			{
				auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_LEFT;
				if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
					p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
					AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
				}
			}
			{
				auto p = my_pos + my_dir + my_dir + E_DIRECTION::E_RIGHT;
				if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
					p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
					AddSkill(p, E_OBJECT::E_EFFECT, 5.f, 1.f);
				}
			}

			if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
				global_effect_id = E_OBJECT::E_EFFECT;
			}
		}
		if (input.GetKey('d')) {
			Vec2 my_pos = objects[my_id]->GetPos();
			E_DIRECTION my_dir = objects[my_id]->GetDirection();
			auto p = my_pos + my_dir;
			if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
				p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
				auto object = make_shared<ShootSkill>(p, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
				object->SetDirection(my_dir);
				createQueue.push_back(object);
			}

			if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
				global_effect_id = E_OBJECT::E_EFFECT;
			}
		}
		if (input.GetKey('q')) {
			inputSkill = 'q';
			skillTimer = 15.0;
			skillSpeed = 5.0;
		}
		if (input.GetKey('w')) {
			inputSkill = 'w';
			skillTimer = 15.0;
			skillSpeed = 5.0;
		}
	}
	else {
		if (0 != objects.count(my_id)) {
			if (input.GetKey(224)) { // ↑/↓/←/→
				CS_MOVE_PACKET sendPacket;
				sendPacket.size = sizeof(CS_MOVE_PACKET);
				sendPacket.type = static_cast<unsigned char>(E_PACKET::E_PACKET_CS_MOVE);
				Vec2 my_pos = objects[my_id]->GetPos();

				if (input.GetKey(72)) { // ↑
					if (my_pos.y - 1 >= 0) {
						sendPacket.dir = static_cast<char>(E_DIRECTION::E_UP);
						packetQueue.AddSendPacket(&sendPacket);
					}
				}
				if (input.GetKey(80)) { // ↓
					if (my_pos.y + 1 < MapSize::CURRENT_MAP_SIZE.y) {
						sendPacket.dir = static_cast<char>(E_DIRECTION::E_DOWN);
						packetQueue.AddSendPacket(&sendPacket);
					}
				}
				if (input.GetKey(75)) { // ←
					if (my_pos.x - 1 >= 0) {
						sendPacket.dir = static_cast<char>(E_DIRECTION::E_LEFT);
						packetQueue.AddSendPacket(&sendPacket);
					}
				}
				if (input.GetKey(77)) { // →
					if (my_pos.x + 1 < MapSize::CURRENT_MAP_SIZE.x) {
						sendPacket.dir = static_cast<char>(E_DIRECTION::E_RIGHT);
						packetQueue.AddSendPacket(&sendPacket);
					}
				}
			}
		}
	}

	if (inputSkill != ' ') {
		double prevTime = skillTimer;
		skillTimer -= elapsedTime * skillSpeed;
		if (skillTimer < 0.0) {
			skillTimer = 0.0;
			skillSpeed = 1.0;
			inputSkill = ' ';
		}

		if (static_cast<int>(prevTime) != static_cast<int>(skillTimer)) { // 스킬 발동 단위
			if (inputSkill == 'q') {
				Vec2 my_pos = objects[my_id]->GetPos();
				E_DIRECTION my_dir = objects[my_id]->GetDirection();
				auto p = my_pos + my_dir;
				if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
					p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
					auto object = make_shared<ShootSkill>(p, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
					object->SetDirection(my_dir);
					createQueue.push_back(object);
				}

				if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
					global_effect_id = E_OBJECT::E_EFFECT;
				}
			}
			else if (inputSkill == 'w') {
				Vec2 my_pos = objects[my_id]->GetPos();
				E_DIRECTION my_dir = objects[my_id]->GetDirection();
				auto p = my_pos + my_dir;
				if (p.x >= 0 && p.x < MapSize::CURRENT_MAP_SIZE.x &&
					p.y >= 0 && p.y < MapSize::CURRENT_MAP_SIZE.y) {
					shared_ptr<ShootSkill> object;
					if (my_dir == E_DIRECTION::E_UP || my_dir == E_DIRECTION::E_DOWN) {
						if (0 == static_cast<int>(skillTimer) % 4) {
							object = make_shared<ShootSkill>(p + E_DIRECTION::E_LEFT, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
						}
						else if (1 == static_cast<int>(skillTimer) % 4 || 3 == static_cast<int>(skillTimer) % 4) {
							object = make_shared<ShootSkill>(p, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
						}
						else {
							object = make_shared<ShootSkill>(p + E_DIRECTION::E_RIGHT, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
						}
					}
					else {
						if (0 == static_cast<int>(skillTimer) % 4) {
							object = make_shared<ShootSkill>(p + E_DIRECTION::E_UP, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
						}
						else if (1 == static_cast<int>(skillTimer) % 4 || 3 == static_cast<int>(skillTimer) % 4) {
							object = make_shared<ShootSkill>(p, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
						}
						else {
							object = make_shared<ShootSkill>(p + E_DIRECTION::E_DOWN, E_OBJECT::E_EFFECT + 2, global_effect_id++, 5.f, 1.f);
						}
					}
					object->SetDirection(my_dir);
					createQueue.push_back(object);
				}

				if (global_effect_id > E_OBJECT::E_EFFECT + 100) {
					global_effect_id = E_OBJECT::E_EFFECT;
				}
			}
		}
	}
	///////
	///////
	///////

	//Update
	Scene::Update(elapsedTime);
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
		if (ac) {
			if (pos.x >= 0					&& pos.y >= 0	&&
				pos.x < MapSize::CURRENT_MAP_SIZE.x	&& pos.y < MapSize::CURRENT_MAP_SIZE.y)
				scene[pos.y][pos.x] = animationMGR.GetAnimationShape(object.second->GetType())[ac->GetAnimationState()];
		}
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
	Vec2 pos{};
	int sight{ 10 };

	if (nullptr != objects[my_id]) {
		pos = objects[my_id]->GetPos();
		sight = objects[my_id]->GetComponent<StatusComponent>()->GetSight();
	}
	for (int i{ pos.y - sight }; i < pos.y + sight; ++i) {
		for (int j{ pos.x - sight }; j < pos.x + sight; ++j) {
			if (i < 0 || j < 0 || i >= MapSize::CURRENT_MAP_SIZE.y || j >= MapSize::CURRENT_MAP_SIZE.x) {
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

void LobbyScene::ProcessPacket(char* p_Packet)
{
	E_PACKET type = static_cast<E_PACKET>(p_Packet[1]);
	auto& animationMGR = AnimationMGR::GetInstance();

	switch (type)
	{
	case E_PACKET::E_PACKET_SC_ADD_PLAYER:
	{
		SC_ADD_PLAYER_PACKET* recvPacket = reinterpret_cast<SC_ADD_PLAYER_PACKET*>(p_Packet);

		auto object = make_shared<Player>(
			Vec2{ recvPacket->posX, recvPacket->posY },
			E_OBJECT::E_CLIENT, recvPacket->id);

		auto& uiMGR = UIMGR::GetInstance();
		auto ui = uiMGR.AddUI<PlayerUI>(0, 21);
		ui->SetPlayer(objects[my_id]);

		createQueue.push_back(object);
		break;
	}
	case E_PACKET::E_PACKET_SC_MOVE:
	{
		SC_MOVE_PACKET* recvPacket = reinterpret_cast<SC_MOVE_PACKET*>(p_Packet);
		if (0 == objects.count(recvPacket->id))
			break;

		E_DIRECTION dir = static_cast<E_DIRECTION>(recvPacket->dir);
		Vec2 my_pos = objects[recvPacket->id]->GetPos();

		switch (dir)
		{
		case E_DIRECTION::E_UP:
			objects[my_id]->SetDirection(E_DIRECTION::E_UP);
			objects[my_id]->Move(E_DIRECTION::E_UP, 1);
			break;
		case E_DIRECTION::E_DOWN:
			objects[my_id]->SetDirection(E_DIRECTION::E_DOWN);
			objects[my_id]->Move(E_DIRECTION::E_DOWN, 1);
			break;
		case E_DIRECTION::E_LEFT:
			objects[my_id]->SetDirection(E_DIRECTION::E_LEFT);
			objects[my_id]->Move(E_DIRECTION::E_LEFT, 1);
			break;
		case E_DIRECTION::E_RIGHT:
			objects[my_id]->SetDirection(E_DIRECTION::E_RIGHT);
			objects[my_id]->Move(E_DIRECTION::E_RIGHT, 1);
			break;
		}

		break;

	}
	}
}
