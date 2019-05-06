#pragma once
#include "SceneManager.h"

namespace e
{
	class GameObject;
	class Scene
	{
		friend std::shared_ptr<Scene> SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);
		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void AddGameObject(const std::string& name, const std::vector<Component*>& pComponents);
		void WakeUp();
		void Update();

	private: 
		std::string m_Name{};
		std::map<std::string, std::shared_ptr<GameObject>> m_spNamedGameObjects;
		std::vector<std::shared_ptr<GameObject>> m_spGameObjects;
	};
}