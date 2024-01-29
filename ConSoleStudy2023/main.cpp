#include "stdafx.h"
#include "GameFramework.h"

int main(int argc, char** argv)
{
	auto& gameFramework = GameFramework::GetInstance();
	gameFramework.Initialize();
	gameFramework.Run();
}
