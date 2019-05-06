#pragma once
#include "Singleton.h"

namespace e
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);

		void WakeUp();
		void Update();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_spScenes;
	};
}