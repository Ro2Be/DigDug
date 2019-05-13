#pragma once
#include <Component.h>
#include "TransformComponent.h"

class TaizoHoriComponent final : public e::Component
{
public:
	//FUNCTIONS
	TaizoHoriComponent() = default;
	virtual void WakeUp(const e::GameObject* pParent) override;
private:
	//VARIABLES
	e::TransformComponent* m_pTransformComponent;
};