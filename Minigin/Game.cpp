#include "MiniginPCH.h"
#include <thread>
#include "Game.h"
#include "Canvas.h"
#include "Engine.h"
#include <thread>

namespace e
{
	using namespace std;

	float Game::dt{ 0 };
	bool Game::m_Quit{ false };
	bool Game::m_Pause{ false };

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

	void Game::Run() const
	{
		thread engine(Engine::Loop); //REMOVE TO RUN WITHOUT ENGINE INTERFACE
		Initialize();
		GameLoop();
		Canvas::GetInstance().Destroy(); //MAYBE MOVE TO TERMINATE
		cout << "PRESS ENTER TO END TO CLOSE THE ENGINE";
		engine.join(); //REMOVE TO RUN WITHOUT ENGINE INTERFACE
		Terminate();
	}

	void Game::Initialize() const
	{
		ResourceManager::GetInstance().Init(m_Settings.name);
		Canvas::GetInstance().Init(m_Settings.name, m_Settings.resolution);
		Load();
		SceneManager::GetInstance().WakeUp(); //WakeUp all gameObjects and components
	}

	void Game::GameLoop() const
	{
		auto& canvas{ Canvas::GetInstance() };
		auto& sceneManager{ SceneManager::GetInstance() };
		auto& inputManager{ InputManager::GetInstance() };
		Chrono chrono{};
		while (!m_Quit)
		{
			if (!m_Pause)
			{
				inputManager.HandleInputEvents(); //TODO GET THIS OUT THE IF STATEMENT, BUT DONT HANDLE INPUT WHILE IN PAUSE
				sceneManager.Update();
				canvas.Render();
			}
			Sleep(1000.f / m_Settings.targetFrameRate - chrono.Get());
			dt = chrono.GetSet();
		}
	}
	void Game::Terminate()
	{
		SDL_Quit();
	}
	void Game::Sleep(float milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(long long(milliseconds)));
	}
}
