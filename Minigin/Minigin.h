#pragma once
#include "Game.h"
#include "Chrono.h"

class Game;
namespace e
{
	class Minigin
	{
	public:
		//VARIABLES
		static float dt;
		static bool quit;
		//FUNCTIONS
		static void Run(const Game& game);
	private:
		//VARIABLES
		static const float targetFrameRate;
		//FUNCTIONS
		static void Load(const Game& game);
		static void GameLoop();
		static void Sleep(float milliseconds);
		static void Terminate();
	};
}