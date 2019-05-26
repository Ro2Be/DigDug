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
		bool GetEndOfAnimation() const;
		void SetLock(bool lock);
		void SetFrame(const unsigned char frameIndex, bool loop = true);
		void SetAnimation(Animation* pAnimation, bool loop = true);
		Animation* GetpAnimation() const;
	private:
		TextureComponent* m_pTextureComponent;
		Animation* m_pAnimation;
		float m_Timer;
		unsigned char m_FrameIndex;
		bool m_Loop;
		bool m_Lock;
	};
}