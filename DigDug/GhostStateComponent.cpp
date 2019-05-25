#include "pch.h"
#include "GhostStateComponent.h"
#include "AnimatorComponent.h"
#include "DefaultStateComponent.h"

namespace Character
{
	using namespace std;

	GhostStateComponent::GhostStateComponent(e::Animation* pAnimation) :
		m_pAnimation{ pAnimation }
	{
	}
	GhostStateComponent::~GhostStateComponent() = default;
	void GhostStateComponent::WakeUp(const e::GameObject* pGameObject)
	{
		pGameObject->GetpComponent<DefaultStateComponent>("GhostStateComponents needs a DefaultStateComponent");
		pGameObject->GetpComponent<e::AnimatorComponent>("GhostStateComponents needs a AnimatorComponent");
	}
	void GhostStateComponent::Update(const e::GameObject* pGameObject)
	{
		const e::SVector thisToTarget{ m_TargetPosition - m_pTransformComponent->position };
		if (1.f < thisToTarget.SqrRadius()) m_pTransformComponent->position += e::SVector(e::FPolarVector(speed, thisToTarget.Angle()));
		else ChangeState(pGameObject, pGameObject->GetpComponent<DefaultStateComponent>());
	}
	void GhostStateComponent::Launch(const e::GameObject* pGameObject)
	{
		pGameObject->GetpComponent<e::AnimatorComponent>("GhostStateComponents needs a AnimatorComponent")->SetAnimation(m_pAnimation);
		m_TargetPosition = m_pTransformComponent->position + e::SVector{ 30, 30 };
	}
	void GhostStateComponent::Finish(const e::GameObject* /*pGameObject*/)
	{
	}
}