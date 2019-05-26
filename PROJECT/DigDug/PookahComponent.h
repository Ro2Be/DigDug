#pragma once
#include <Component.h>
class PookahComponent final : public e::Component
{
public:
	PookahComponent();
	virtual ~PookahComponent() override;
	void WakeUp(const e::GameObject*) override;
	void Update(const e::GameObject*) override;
};