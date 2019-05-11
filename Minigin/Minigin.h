#pragma once
//#include "Renderer.h"

class GameScene;
class SceneManager;
class CollisionManager;
class MusicManager;

namespace dae
{
	class Renderer;
}
class Time;
class InputManager;
struct SDL_Window;

class Minigin
{
public:
	Minigin() = default;
	~Minigin() = default;


	void Initialize(int width, int height);
	void RunGame();

	void DoStuff();

	void AddGameScene(GameScene* pScene);

	Minigin(const Minigin& obj) = delete;
	Minigin(Minigin&& obj) noexcept = delete;

	Minigin& operator=(const Minigin& obj) = delete;
	Minigin& operator=(Minigin&& obj) noexcept = delete;

	void Destroy();
private:
	SceneManager* m_SceneManager;
	dae::Renderer* m_Renderer;
	MusicManager* m_MusicManager;
	CollisionManager* m_CollisionManager;
	Time* m_Time;
	InputManager* m_Input;
    SDL_Window* m_Window = nullptr;

	SDL_Window* InitializeWindow(int width, int height);
};