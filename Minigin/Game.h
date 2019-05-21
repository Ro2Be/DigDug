#pragma once
#include "Scene.h"
#include "Components.h"
#include "Managers.h"
namespace e
{
	class Game
	{
	public:
		struct Settings
		{
			std::string name;
			SVector resolution;
			const float targetFrameRate;
		};
		//VARIABLES
		static float dt;
		//FUNCTIONS
		static void Quit();
		Game(const Settings& settings);
		virtual ~Game() = default;
		void Run() const;
		const Settings& GetSettings() const;
	protected:
		virtual void Load() const = 0;
	private:
		//VARIABLES
		static bool m_Quit;
		Settings m_Settings;
		//FUNCTIONS
		void Initialize() const;
		void GameLoop() const;
		static void Terminate();
		static void Sleep(float milliseconds);
	};
}