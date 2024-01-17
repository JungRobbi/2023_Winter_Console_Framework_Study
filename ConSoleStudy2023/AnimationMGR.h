#pragma once
#include "stdafx.h"

class AnimationMGR
{
	unordered_map<int, string> Object_Shapes;
	unordered_map<int, vector<int>> Object_Animation;

private:
	AnimationMGR() = default;
	AnimationMGR(const AnimationMGR&) = delete;
	AnimationMGR& operator=(const AnimationMGR&) = delete;
	AnimationMGR(AnimationMGR&&) = delete;
	AnimationMGR& operator=(AnimationMGR&&) = delete;
	~AnimationMGR() = default;
public:
	static AnimationMGR& GetInstance();
	void Initialize();
	void Update(double elapsedTime);

	string GetShape(int index);
	vector<int> GetAnimationShape(int index);
};

