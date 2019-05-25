#pragma once
#include <Component.h>
#include "EventObserver.h"

class HealthDisplayComponent final : public e::Component, public e::EventObserver
{
public:
	static HealthDisplayComponent* pHealthDisplayComponent; //ugly singleton design pattern: couple the uncoupled because it works
	HealthDisplayComponent() { pHealthDisplayComponent = this; };
	virtual ~HealthDisplayComponent() override { pHealthDisplayComponent = nullptr; };
	virtual void WakeUp(const e::GameObject*) override;;
	virtual void Update(const e::GameObject*) override;;
	virtual void Observe(const e::Event* pEvent) override;
};