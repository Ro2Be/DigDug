#include "MiniginPCH.h"
#include "Engine.h"
#include "Game.h"

namespace e
{
	std::unordered_map<std::string, Engine::Command> Engine::m_CommandsByName
	{
		{ "", Command::Empty },
		{ "Pause", Command::Pause },
		{ "Unpause", Command::Unpause },
		{ "ShowGameObjects", Command::ShowGameObjects }
	};

	using namespace std;
	Engine::Engine()
	{
	}
	Engine::~Engine()
	{
	}
	void Engine::Loop()
	{
		while (!Game::m_Quit)
		{
			string input;
			getline(cin, input);
			auto it{ m_CommandsByName.find(input) };
			if (it == m_CommandsByName.end())
			{
				cout << "Command does not exist\n\n";
			}
			else switch((*it).second)
			{
			case Command::Empty :
				break;
			case Command::Pause :
				Game::m_Pause = true;
				cout << "--- GAME PAUSED ---\n";
				cout << "-------------------\n";
				break;
			case Command::Unpause :
				Game::m_Pause = false;
				cout << "-- GAME UNPAUSED --\n";
				cout << "-------------------\n";
				break;
			case Command::ShowGameObjects :
				cout << '\n';
				e::SceneManager::GetInstance().GetspActiveScene()->PrintGameObjectNames();
				break;
			default :
				break;
			}
		}
	}
}
