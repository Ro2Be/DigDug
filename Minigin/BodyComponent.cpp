#include "MiniginPCH.h"
#include "BodyComponent.h"
#include "Game.h"

namespace e
{
	using namespace std;
	void BodyComponent::WakeUp(const GameObject* pParent)
	{
		if (TransformComponent* pTransformComponent = pParent->GetpComponent<TransformComponent>())
		{
			m_pTransformComponent = pTransformComponent;
		}
		else throw runtime_error("Make sure each BodyComponent has a TransformComponent sibling!");
	}

	void BodyComponent::Update(const GameObject*)
	{
		m_pTransformComponent->position.x += short(float(m_Velocity.x) * Game::dt);
		m_pTransformComponent->position.y += short(float(m_Velocity.y) * Game::dt);
	}

	void BodyComponent::SetVelocity(const SVector & velocity)
	{
		m_Velocity = velocity;
	}
}