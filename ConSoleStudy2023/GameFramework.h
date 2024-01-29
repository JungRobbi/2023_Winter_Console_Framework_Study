#pragma once
class GameFramework
{
private:
	GameFramework() = default;
	GameFramework(const GameFramework&) = delete;
	GameFramework& operator=(const GameFramework&) = delete;
	GameFramework(GameFramework&&) = delete;
	GameFramework& operator=(GameFramework&&) = delete;
	~GameFramework() = default;
public:
	static GameFramework& GetInstance();

	void Initialize();
	void Run();
	void Destroy();
	void ChangeScene(E_SCENE type);
};
