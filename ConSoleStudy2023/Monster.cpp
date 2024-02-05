#include "Monster.h"
#include "MonsterWanderState.h"
#include "MonsterTrackingState.h"
#include "MonsterAttackState.h"

#include "AnimationComponent.h"

Monster::Monster() 
	: Object(), monsterFSM(make_shared<FSM>(this, make_shared<MonsterWanderState>())),
	flag(E_FSM_STATE::E_FSM_WANDER), currentState(E_FSM_STATE::E_FSM_WANDER)
{
	objectType = E_OBJECT::E_ENEMY;
}

Monster::Monster(Vec2 Pos, int type, unsigned long long id) 
	: Object(Pos, id), monsterFSM(make_shared<FSM>(this, make_shared<MonsterWanderState>())),
	flag(E_FSM_STATE::E_FSM_WANDER), currentState(E_FSM_STATE::E_FSM_WANDER)
{
	objectType = type;
}

Monster::~Monster()
{
}

void Monster::Start()
{
	auto& animationMGR = AnimationMGR::GetInstance();
	AddComponent<MovementComponent>();
	AddComponent<AttackComponent>();
	AddComponent<StatusComponent>();
	auto component = AddComponent<AnimationComponent>();
	component->SetAnimationStateMAX(animationMGR.GetAnimationShape(objectType).size());
}

void Monster::Update(double elapsedTime)
{
	Object::Update(elapsedTime);

	if (monsterFSM) {
		if (currentState != flag) {
			currentState = flag;
			switch (flag)
			{
			case E_FSM_STATE::E_FSM_WANDER:
				monsterFSM->ChangeState(std::make_shared<MonsterWanderState>());
				break;
			case E_FSM_STATE::E_FSM_TRACKING:
				monsterFSM->ChangeState(std::make_shared<MonsterTrackingState>());
				break;
			case E_FSM_STATE::E_FSM_ATTACK:
				monsterFSM->ChangeState(std::make_shared<MonsterAttackState>());
				break;
			default:
				break;
			}
		}

		monsterFSM->Update(elapsedTime);
	}
}

shared_ptr<Object> Monster::GetTarget()
{
	return target;
}

void Monster::SetTarget(shared_ptr<Object> tar)
{
	target = tar;
}

void Monster::SetFSMState(E_FSM_STATE state)
{
	flag = state;
}

// 원형 거리
//double DistanceVec2(Vec2 a, Vec2 b) {
//	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
//}


// (가로 + 세로) 값
//double DistanceVec2(Vec2 a, Vec2 b) {
//	return abs(a.x - b.x) + abs(a.y - b.y);
//}

// 바라보는 시야
double DistanceVec2(Vec2 a, Vec2 b) {
	return max(abs(a.x - b.x), abs(a.y - b.y));
}
