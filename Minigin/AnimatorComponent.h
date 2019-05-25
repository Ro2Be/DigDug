#pragma once
#include "Component.h"
#include "TextureComponent.h"

namespace e
{
	struct Animation;
	class AnimatorComponent final : public Component
	{
	public:
		AnimatorComponent();
		explicit AnimatorComponent(const std::string& animation);
		virtual void WakeUp(const GameObject* pParent) override;
		virtual void Update(const GameObject* pParent) override;
		void SetFrame(const unsigned char frameIndex);
		void SetAnimation(Animation* pAnimation);
		Animation* GetpAnimation() const;
	private:
		TextureComponent* m_pTextureComponent;
		Animation* m_pAnimation;
		float m_Timer;
		unsigned char m_FrameIndex;
	};
}