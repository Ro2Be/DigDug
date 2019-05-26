#pragma once
#include <StateComponent.h>
#include "Event.h"
#include "AnimatorComponent.h"
namespace Character
{
	struct DeathEvent final : public e::Event
	{
		DeathEvent(const e::GameObject* pGameObject) :
			Event(),
			pGameObject{ pGameObject }
		{}
		virtual ~DeathEvent() override = default;
		const e::GameObject* pGameObject;
	};

	class DieStateComponent final : public e::StateComponent
	{
	public:
		explicit DieStateComponent(e::Animation* pAnimation);
		virtual ~DieStateComponent() = default;
		virtual void WakeUp(const e::GameObject* pGameObject) override;
		virtual void Update(const e::GameObject* pGameObject) override;
	protected:
		virtual void Launch(const e::GameObject* pGameObject) override;
		virtual void Finish(const e::GameObject* pGameObject) override;
	private:
		e::AnimatorComponent* m_pAnimatorComponent;
		e::EventNotifier m_EventNotifier;
		e::Animation* m_pAnimation;
	};
}