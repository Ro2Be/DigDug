#pragma once
#include "Components.h"
namespace e
{
	class AnimationComponent : public Component
	{
	public:
		AnimationComponent(const std::string& animationName);
		virtual void WakeUp(const GameObject* pParent) override;
		virtual void Update(const GameObject* pParent) override;
	private:
		TextureComponent* m_pTextureComponent;
		char m_FrameIndex;
		float m_Timer;
		Animation* m_pAnimation;
	};
}