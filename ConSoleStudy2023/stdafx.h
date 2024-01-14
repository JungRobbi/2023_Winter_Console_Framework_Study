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

static const int StageSizeX = 101;
static const int StageSizeY = 101;

static const float EFFECT_MAX = 1000000.f;

static const int MONSTER_EYESIGHT = 2;

enum E_DIRECTION {
	E_UP, E_DOWN, E_LEFT, E_RIGHT
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

	bool operator==(const Vec2 rhs) 
	{
		return x == rhs.x && y == rhs.y;
	}
};