#include "AnimationMGR.h"

AnimationMGR& AnimationMGR::GetInstance()
{
	static AnimationMGR instance;
	return instance;
}

void AnimationMGR::Initialize()
{
	Object_Shapes = unordered_map<int, string>{};
	Object_Animation = unordered_map<int, vector<int>>{};

	Object_Shapes[E_OBJECT::E_CLIENT] = "¡Ú";
	Object_Shapes[E_OBJECT::E_CLIENT + 1] = "¡Ù";
	Object_Shapes[E_OBJECT::E_ENEMY] = "¡Ý";
	Object_Shapes[E_OBJECT::E_ENEMY + 1] = "¡Û";
	Object_Shapes[E_OBJECT::E_WALL] = "¡à";
	Object_Shapes[E_OBJECT::E_WALL + 1] = "¡á";
	Object_Shapes[E_OBJECT::E_TILE] = "  ";
	Object_Shapes[E_OBJECT::E_TILE + 1] = "¡à";
	Object_Shapes[E_OBJECT::E_TILE + 2] = "¡á";
	Object_Shapes[E_OBJECT::E_TILE + 3] = "¦¡ ";
	Object_Shapes[E_OBJECT::E_TILE + 4] = "¦¢ ";
	Object_Shapes[E_OBJECT::E_TILE + 5] = "¦« ";
	Object_Shapes[E_OBJECT::E_TILE + 6] = "¡Ü";
	Object_Shapes[E_OBJECT::E_EFFECT] = "¨ç";
	Object_Shapes[E_OBJECT::E_EFFECT + 1] = "¨è";
	Object_Shapes[E_OBJECT::E_EFFECT + 2] = "¨é";
	Object_Shapes[E_OBJECT::E_EFFECT_ATTACK] = "¡Ø";
	Object_Shapes[E_OBJECT::E_EFFECT_ATTACK + 1] = "¢Â";

	{
		Object_Animation[E_OBJECT::E_CLIENT].emplace_back(E_OBJECT::E_CLIENT);
		Object_Animation[E_OBJECT::E_CLIENT].emplace_back(E_OBJECT::E_CLIENT + 1);
	}
	{
		Object_Animation[E_OBJECT::E_ENEMY].emplace_back(E_OBJECT::E_ENEMY);
		Object_Animation[E_OBJECT::E_ENEMY].emplace_back(E_OBJECT::E_ENEMY + 1);
	}
	{
		Object_Animation[E_OBJECT::E_WALL].emplace_back(E_OBJECT::E_WALL);
	}
	{
		Object_Animation[E_OBJECT::E_WALL + 1].emplace_back(E_OBJECT::E_WALL);
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
		Object_Animation[E_OBJECT::E_EFFECT + 2].emplace_back(E_OBJECT::E_EFFECT_ATTACK + 1);
	}
}

void AnimationMGR::Update(double elapsedTime)
{
}

string AnimationMGR::GetShape(int index)
{
	if (Object_Shapes.find(index) == Object_Shapes.end())
		return ""s;
	return Object_Shapes[index];
}

vector<int> AnimationMGR::GetAnimationShape(int index) 
{
	if (Object_Animation.find(index) == Object_Animation.end())
		return vector<int>{};
	return Object_Animation[index];
}