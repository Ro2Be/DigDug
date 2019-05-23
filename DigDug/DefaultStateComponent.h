#pragma once
#include "StateComponent.h"
#include "ColliderComponent.h"

namespace Character
{
	class DefaultStateComponent final : public e::StateComponent, public e::CollisionHandler
	{
	public:
		explicit DefaultStateComponent() { isActive = true; };
		~DefaultStateComponent() override = default;
		virtual void WakeUp(const e::GameObject* pGameObject) override;
		virtual void Update(const e::GameObject* pGameObject) override;
		virtual void HandleCollision(const e::GameObject* pGameObject, const e::GameObject* pOther) override;
	protected:
		virtual void Launch(const e::GameObject* pGameObject) override;
		virtual void Finish(const e::GameObject* pGameObject) override;
	private:
		const e::ColliderComponent* m_pColliderComponent;
	};
}