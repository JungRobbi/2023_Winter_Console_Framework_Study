#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>
#include <unordered_map>
#include <algorithm>

using namespace std;
using namespace chrono;

static const int StageSizeX = 11;
static const int StageSizeY = 11;

static const float EFFECT_MAX = 1000000.f;