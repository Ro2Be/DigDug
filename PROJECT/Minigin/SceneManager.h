#pragma once
#include "Singleton.h"

namespace e
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);
		std::shared_ptr<Scene> GetspActiveScene();
		void WakeUp();
		void Update();
		void Render();

	private:
		char m_ActiveSceneIndex{ 0 };
		std::vector<std::shared_ptr<Scene>> m_spScenes;
	};
}