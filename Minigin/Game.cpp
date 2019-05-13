#include "MiniginPCH.h"
#include <thread>
#include "Game.h"
#include "Canvas.h"

namespace e
{
	using namespace std;

	float Game::dt{ 0 };
	bool Game::m_Quit{ false };

	void Game::Quit()
	{
		Game::m_Quit = true;
	}

	Game::Game(const Settings& settings) :
		m_Settings{ settings }
	{
	}

	const Game::Settings& Game::GetSettings() const
	{
		return m_Settings;
	}

	void Game::Run()
	{
		Initialize();
		GameLoop();
		Terminate();
	}

	void Game::Initialize()
	{
		ResourceManager::GetInstance().Init(m_Settings.name);
		Canvas::GetInstance().Init(m_Settings.name, m_Settings.resolution);
		Load();
		SceneManager::GetInstance().WakeUp(); //WakeUp all gameObjects and components
	}

	void Game::GameLoop()
	{
		auto& canvas{ Canvas::GetInstance() };
		auto& sceneManager{ SceneManager::GetInstance() };
		auto& inputManager{ InputManager::GetInstance() };
		Chrono chrono{};
		while (!m_Quit)
		{
			inputManager.HandleInputEvents();
			sceneManager.Update();
			canvas.Render();
			Sleep(1000.f / m_Settings.targetFrameRate - chrono.Get());
			dt = chrono.GetSet();
		}
	}

	void Game::Terminate()
	{
		Canvas::GetInstance().Destroy();
		SDL_Quit();
	}

	void Game::Sleep(float milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(long long(milliseconds)));
	}
}