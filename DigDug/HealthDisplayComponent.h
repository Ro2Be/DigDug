#pragma once
#include <Component.h>
#include "EventObserver.h"
#include "TileMapComponent.h"
class HealthDisplayComponent final : public e::Component, public e::EventObserver
{
public:
	static HealthDisplayComponent* pHealthDisplayComponent; //ugly singleton design pattern: couple the uncoupled because it works
	HealthDisplayComponent();
	virtual ~HealthDisplayComponent() override { pHealthDisplayComponent = nullptr; };
	virtual void WakeUp(const e::GameObject*) override;
	virtual void Update(const e::GameObject*) override;
	virtual void Observe(const e::Event* pEvent) override;
	void GainLive();
	void LoseLive();
private:
	char m_Lives;
	e::TileMapComponent<1, 5>* m_pTileMapComponent;
};