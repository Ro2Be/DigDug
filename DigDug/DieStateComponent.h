#pragma once
#include <StateComponent.h>

namespace Character
{
	class DieStateComponent : public e::StateComponent
	{
	public:
		DieStateComponent() = default;
		virtual ~DieStateComponent() = default;
		virtual void WakeUp(const e::GameObject* pGameObject) override;
		virtual void Update(const e::GameObject* pGameObject) override;
	protected:
		virtual void Launch(const e::GameObject* pGameObject) override;
		virtual void Finish(const e::GameObject* pGameObject) override;
	private:
		float m_Timer;
	};
}