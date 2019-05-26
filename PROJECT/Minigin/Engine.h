#pragma once

namespace e
{
	class Game;
	class Engine
	{
	public:
		Engine();
		~Engine();
		static void Loop();
	private:
		enum class Command : int { Empty, Pause, Unpause, ShowGameObjects };
		static std::unordered_map<std::string, Command> m_CommandsByName;
	};
}