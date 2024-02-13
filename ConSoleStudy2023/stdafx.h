#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <cmath>
#include <list>

#include "../Global.h"

using namespace std;
using namespace chrono;

const int STAGE_SIZE_X = 101;
const int STAGE_SIZE_Y = 101;
const int LOBBY_SIZE_X = 21;
const int LOBBY_SIZE_Y = 21;

const float EFFECT_MAX = 1000000.f;

enum class E_DIRECTION {
	E_UP, E_DOWN, E_LEFT, E_RIGHT,
	E_RIGHT_UP, E_RIGHT_DOWN
};

enum E_OBJECT {
	E_CLIENT = 0,
	E_ENEMY = 10000,
	E_WALL = 20000,
	E_ITEM = 20100,
	E_TILE = 20200,
	E_EFFECT = 30000,
	E_EFFECT_ATTACK = 40000,
};

struct Vec2 {
	int x, y;

	Vec2 operator+(E_DIRECTION dir)
	{
		switch (dir)
		{
		case E_DIRECTION::E_UP:
			return Vec2{ x, y - 1 };
		case E_DIRECTION::E_DOWN:
			return Vec2{ x, y + 1 };
		case E_DIRECTION::E_LEFT:
			return Vec2{ x - 1, y };
		case E_DIRECTION::E_RIGHT:
			return Vec2{ x + 1, y };
		default:
			break;
		}
	}

	void operator+=(E_DIRECTION dir)
	{
		
		switch (dir)
		{
		case E_DIRECTION::E_UP:
			y -= 1;
			break;
		case E_DIRECTION::E_DOWN:
			y += 1;
			break;
		case E_DIRECTION::E_LEFT:
			x -= 1;
			break;
		case E_DIRECTION::E_RIGHT:
			x += 1;
			break;
		default:
			break;
		}
	}

	Vec2 operator-(const Vec2 rhs)
	{
		return Vec2{ x - rhs.x, y - rhs.y };
	}

	bool operator==(const Vec2 rhs) 
	{
		return x == rhs.x && y == rhs.y;
	}
};

static Vec2 CURRENT_MAP_SIZE{};