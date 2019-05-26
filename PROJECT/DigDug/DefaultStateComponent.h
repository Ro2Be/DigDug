#pragma once
#include "StateComponent.h"
#include "ColliderComponent.h"

namespace Character
{
	class DefaultStateComponent final : public e::StateComponent
	{
	public:
		explicit DefaultStateComponent(e::Animation* pAnimation);
		~DefaultStateComponent() override = default;
		virtual void WakeUp(const e::GameObject* pGameObject) override;
		virtual void Update(const e::GameObject* pGameObject) override;
	protected:
		virtual void Launch(const e::GameObject* pGameObject) override;
		virtual void Finish(const e::GameObject* pGameObject) override;
	private:
		e::Animation* m_pAnimation;
	};
}