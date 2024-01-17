#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <cmath>
#include <list>

using namespace std;
using namespace chrono;

static const int STAGE_SIZE_X = 101;
static const int STAGE_SIZE_Y = 101;

static const float EFFECT_MAX = 1000000.f;

enum E_DIRECTION {
	E_UP, E_DOWN, E_LEFT, E_RIGHT
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
		case E_UP:
			return Vec2{ x, y - 1 };
		case E_DOWN:
			return Vec2{ x, y + 1 };
		case E_LEFT:
			return Vec2{ x - 1, y };
		case E_RIGHT:
			return Vec2{ x + 1, y };
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