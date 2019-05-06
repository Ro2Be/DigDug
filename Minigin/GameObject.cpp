#include "MiniginPCH.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Canvas.h"

namespace e
{
	using namespace std;

	GameObject::GameObject(const std::vector<Component*>& pComponents)
	{
		for (Component* pComponent : pComponents) Add(pComponent);
	}
	GameObject::~GameObject()
	{
		for (Component* pComponent : m_pComponents) delete pComponent;
	}
	void GameObject::Add(Component* pC)
	{
		m_pComponents.push_back(pC);
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