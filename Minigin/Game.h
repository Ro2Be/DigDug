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
		};
		Game(const Settings& settings);
		~Game() = default;
		virtual void Load() const = 0;
		const Settings& GetSettings() const;
	private:
		Settings m_Settings;
	};
}