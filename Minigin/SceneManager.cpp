#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

namespace e
{
	using namespace std;

	void SceneManager::WakeUp()
	{
		for (const shared_ptr<Scene> spScene : m_spScenes) spScene->WakeUp();
	}
	void SceneManager::Update()
	{
		for (shared_ptr<Scene> spScene : m_spScenes) spScene->Update();
	}
	shared_ptr<Scene> SceneManager::CreateScene(const std::string& name)
	{
		const shared_ptr<Scene> spScene = make_shared<Scene>(name);
		m_spScenes.push_back(spScene);
		return spScene;
	}
	std::shared_ptr<Scene> SceneManager::GetspActiveScene()
	{
		return m_spScenes[m_ActiveSceneIndex];
	}
}
