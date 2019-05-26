#pragma once
#include "Component.h"
namespace e
{
	class FPSComponent final : public Component
	{
	public:
		void Update(const GameObject* parent) override;
	};
}