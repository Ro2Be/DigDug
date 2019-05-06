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
	void Scene::AddGameObject(const std::string& name, const std::vector<Component*>& pComponents)
	{
		UNREFERENCED_PARAMETER(name);
		//m_spNamedGameObjects[name] = make_shared<GameObject>(pComponents);
		m_spGameObjects.push_back(make_shared<GameObject>(pComponents));
	}
	void Scene::WakeUp()
	{
		for (shared_ptr<GameObject> spGameObject : m_spGameObjects) spGameObject->WakeUp();
	}
	void Scene::Update()
	{
		for (shared_ptr<GameObject> spGameObject : m_spGameObjects) spGameObject->Update();
	}
}