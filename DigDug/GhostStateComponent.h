#pragma once
#include "StateComponent.h"
#include "TransformComponent.h"

namespace Character
{
	class GhostStateComponent final : public e::StateComponent
	{
	public:
		GhostStateComponent(e::Animation* pAnimation);
		virtual ~GhostStateComponent() override;
		virtual void WakeUp(const e::GameObject*) override;
		virtual void Update(const e::GameObject*) override;
	protected:
		virtual void Launch(const e::GameObject* pGameObject) override;
		virtual void Finish(const e::GameObject* pGameObject) override;
	private:
		e::TransformComponent* m_pTransformComponent;
		e::SPoint m_TargetPosition;
		const float speed{ 10.f };
		e::Animation* m_pAnimation;
	};
}