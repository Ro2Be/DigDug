#pragma once
#include "Component.h"
#include <vector>
#include "TextureComponent.h"

namespace e
{
	struct Animation;
	class AnimatorComponent final : public Component
	{
	public:
		explicit AnimatorComponent(const std::string& animation);
		explicit AnimatorComponent(const std::vector<std::string>& animations);
		virtual void WakeUp(const GameObject* pParent) override;
		virtual void Update(const GameObject* pParent) override;
		void FlipHorizontal() const;
		void FlipVertical() const;
		void SetFrame(const unsigned char frameIndex);
		void SetAnimation(const unsigned char animationIndex);
	private:
		TextureComponent* m_pTextureComponent;
		unsigned char m_FrameIndex;
		unsigned char m_AnimationIndex;
		float m_Timer;
		std::vector<Animation*> m_pAnimations;
	};
}