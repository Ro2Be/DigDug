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

		GameObject* AddGameObject(const std::string& name, const std::vector<Component*>& pComponents);
		GameObject* GetGameObject(const std::string& name);
		void PrintGameObjectNames();
		void WakeUp();
		void Update();

	private: 
		std::string m_Name{};
		std::vector<GameObject> m_GameObjects;
		std::vector<std::string> m_GameObjectNames;
	};
}