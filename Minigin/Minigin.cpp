#include "MiniginPCH.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#pragma comment(lib,"xinput.lib")

#include "MiniginPCH.h"
#include "Minigin.h"

#include "SDL.h"
#include <chrono>
#include <thread>
#include <algorithm>
#include <ctime>
#include <ratio>

#include "ResourceManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Time.h"
#include "InputManager.h"
#include "MusicManager.h"
#include "CollisionManager.h"
#include "PoolManager.h"

#include "GameScene.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  

int main(int argc, char* argv[])
{
   #pragma warning( pop )
	return 0;
}
void Minigin::Initialize(int width, int height)
{
	m_Window = InitializeWindow(width, height);

	m_Renderer = &dae::Renderer::GetInstance();
	m_Renderer->Init(m_Window, float(height));

	m_CollisionManager = &CollisionManager::GetInstance();
	m_CollisionManager->LoadWindow(width, height);

	m_Time = &Time::GetInstance();
	
	m_MusicManager = &MusicManager::GetInstance();
		
	m_Input = &InputManager::GetInstance();
	
	PoolManager::GetInstance();

	dae::ResourceManager::GetInstance().Init("../Data/");
}

void Minigin::Destroy()
{
	m_Renderer->Destroy();
	m_Time->DestroyInstance();
	m_MusicManager->Destroy();
	m_CollisionManager->GetInstance().DestroyInstance();
	m_SceneManager->Destroy();
	PoolManager::GetInstance().Destroy();

	SDL_DestroyWindow(m_Window);
	Mix_CloseAudio();
	SDL_Quit();
}

SDL_Window* Minigin::InitializeWindow(const int width, const int height)
{
	SDL_Window* window;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::stringstream ss; ss << "SDL_Init Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);

	if (!window) {
		std::stringstream ss; ss << "SDL_CreateWindow Error: " << SDL_GetError();
		throw std::runtime_error(ss.str().c_str());
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_Mixer error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return nullptr;
	}

	return window;
}
void Minigin::RunGame()
{
	try
	{
	const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps

	m_SceneManager = &SceneManager::GetInstance();

	std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

	std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();

	bool doContinue = true;

	while (doContinue)
	{
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> clock = std::chrono::duration_cast<std::chrono::duration<double>>(end - begin);

		float elapsed = clock.count();

		m_Time->Update(elapsed);

		doContinue = m_Input->ProcessInput();

		m_SceneManager->Update();
		m_MusicManager->Update();
		m_CollisionManager->Update();

		m_Renderer->Render();

		if (doContinue)doContinue = !m_SceneManager->IsGameOver();

		begin = end;

		t += std::chrono::milliseconds(msPerFrame);
		std::this_thread::sleep_until(t);

		//doContinue = false;
	}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		std::cin.get();
	}
}
void Minigin::AddGameScene(GameScene* pScene)
{
	SceneManager::GetInstance().AddScene(pScene);
}