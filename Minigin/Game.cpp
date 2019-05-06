#include "MiniginPCH.h"
#include "Game.h"

namespace e
{
	Game::Game(const Settings& settings) :
		m_Settings{ settings }
	{
	}

	const Game::Settings& Game::GetSettings() const
	{
		return m_Settings;
	}
}