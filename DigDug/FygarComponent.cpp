#include "pch.h"
#include "FygarComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

void FygarComponent::WakeUp(const e::GameObject* pGameObject)
{
	m_CommandMoveLeft	= pGameObject->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ -speed, 0 });
	m_CommandMoveDown	= pGameObject->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ -0, speed });
	m_CommandMoveRight	= pGameObject->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ speed, -0 });
	m_CommandMoveUp		= pGameObject->GetpComponent<e::TransformComponent>()->CreateMoveCommand({ 0, -speed });
}
void FygarComponent::Update(const e::GameObject*)
{

}
void FygarComponent::HandleCollision(const e::GameObject* /*pGameObject*/, const e::GameObject* /*pOtherGameObject*/)
{

}