#include "MiniginPCH.h"
#include "GameObject.h"

namespace e
{
	using namespace std;

	GameObject::GameObject(const std::vector<Component*>& pComponents)
	{
		for(Component* pComponent : pComponents) m_pComponents.push_back(pComponent);
	}
	GameObject::~GameObject()
	{
		for (Component* pComponent : m_pComponents) delete pComponent;
	}
	GameObject::GameObject(GameObject&& other)
	{
		m_pComponents = std::move(other.m_pComponents);
	}
	void GameObject::WakeUp()
	{
		for (Component* pComponent : m_pComponents) pComponent->WakeUp(this);
	}
	void GameObject::Update()
	{
		for (Component* pComponent : m_pComponents) if (pComponent->isActive) pComponent->Update(this);
	}
}