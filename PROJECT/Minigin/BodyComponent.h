#pragma once
#include "TransformComponent.h"

namespace e
{
	class BodyComponent : public Component
	{
	public:
		BodyComponent() = default;
		void WakeUp(const GameObject* pParent) override;
		void Update(const GameObject* pParent) override;
		void SetVelocity(const SVector& velocity);
	private:
		TransformComponent* m_pTransformComponent;
		SVector m_Velocity;
	};
}
