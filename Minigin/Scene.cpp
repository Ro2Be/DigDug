#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

namespace e
{
	using namespace std;

	Scene::Scene(const string& name) : 
		m_Name{ name }
	{
	}
	GameObject* Scene::AddGameObject(const std::string& name, const std::vector<Component*>& pComponents)
	{
		m_GameObjects.push_back(pComponents);
		m_GameObjectNames.push_back(name);
		return &m_GameObjects.back();
	}
	GameObject* Scene::GetGameObject(const std::string& name)
	{
		for (int i{}; i < m_GameObjectNames.size(); ++i)
		{
			if (m_GameObjectNames[i] == name) return &m_GameObjects[i];
		}
		return nullptr;
	}
	void Scene::PrintGameObjectNames()
	{
		cout << "--- GAMEOBJECTS ---\n";
		for (string name : m_GameObjectNames) cout << name << '\n';
		cout << "-------------------\n\n";
	}
	void Scene::WakeUp()
	{
		for (GameObject& gameObject : m_GameObjects) gameObject.WakeUp();
	}
	void Scene::Update()
	{
		for (GameObject& gameObject : m_GameObjects) gameObject.Update();
	}
}