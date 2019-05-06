#pragma once
#include "Components.h"
namespace e
{
	class AnimationComponent : public Component
	{
	public:
		AnimationComponent(const std::string& animationName);
		void WakeUp(const GameObject* pParent) override;
		virtual void Update(const GameObject* pParent) override;
	private:
		TextureComponent* m_pTextureComponent;
		char frameIndex;
		float timer;
		Animation* pAnimation;
	};
}