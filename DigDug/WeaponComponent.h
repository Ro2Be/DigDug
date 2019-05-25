#pragma once
#include "Component.h"

class WeaponComponent final :public e::Component
{
public:
	WeaponComponent();
	virtual ~WeaponComponent() override;
	void Fire();
	virtual void WakeUp(const e::GameObject*) override;
	virtual void Update(const e::GameObject*) override;
private:
	const e::GameObject* m_pGameObject;
};