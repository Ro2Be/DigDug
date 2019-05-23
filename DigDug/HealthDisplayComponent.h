#pragma once
#include <Component.h>
#include "EventObserver.h"

class HealthDisplayComponent final : public e::Component, public e::EventObserver
{
public:
	HealthDisplayComponent() = default;
	virtual ~HealthDisplayComponent() override = default;
	virtual void WakeUp(const e::GameObject*) override;;
	virtual void Update(const e::GameObject*) override;;
	virtual void Observe(const e::Event& event) override;
};