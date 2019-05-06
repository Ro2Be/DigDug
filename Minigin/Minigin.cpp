#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Canvas.h"

#include "Components.h"
#include "Game.h"

namespace e
{
	using namespace std;
	float Minigin::dt{ 0 };
	bool Minigin::quit{ false };
	const float Minigin::targetFrameRate{ 60.f };

	void Minigin::Run(const Game& game)
	{
		Load(game);
		GameLoop();
		Terminate();
	}

	void Minigin::Load(const Game& game)
	{
		ResourceManager::GetInstance().Init(game.GetSettings().name);
		Canvas::GetInstance().Init(game.GetSettings().name, game.GetSettings().resolution);
		game.Load();
		SceneManager::GetInstance().WakeUp(); //WakeUp all gameObjects and components
	}

	void Minigin::GameLoop()
	{
		auto& canvas{ Canvas::GetInstance() };
		auto& sceneManager{ SceneManager::GetInstance() };
		auto& inputManager{ InputManager::GetInstance() };
		Chrono chrono{};
		while (!quit)
		{
			inputManager.HandleInput();
			sceneManager.Update();
			canvas.Render();
			Sleep(1000.f / targetFrameRate - chrono.Get());
			dt = chrono.GetSet();
		}
	}

	void Minigin::Sleep(float milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(long long(milliseconds)));
	}

	void Minigin::Terminate()
	{
		Canvas::GetInstance().Destroy();
		SDL_Quit();
	}
}