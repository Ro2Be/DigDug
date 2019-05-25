#include "MiniginPCH.h"
#include "AnimatorComponent.h"
#include "ResourceManager.h"
#include "Game.h"

namespace e
{
	using namespace std;
	AnimatorComponent::AnimatorComponent() :
		m_pTextureComponent{ nullptr },
		m_FrameIndex{ 0 },
		m_pAnimation{ nullptr },
		m_Timer{ 0 }
	{
	}
	AnimatorComponent::AnimatorComponent(const std::string& animation) :
		m_pTextureComponent{ nullptr },
		m_FrameIndex{ 0 },
		m_pAnimation{ ResourceManager::GetInstance().GetpAnimation(move(animation)) },
		m_Timer{ m_pAnimation->msPerFrame }
	{
	}
	void AnimatorComponent::WakeUp(const GameObject* pParent)
	{
		m_pTextureComponent = pParent->GetpComponent<TextureComponent>("Make sure each TextComponent has a TextureComponent sibling!");
		if(m_pAnimation) m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
	}
	void AnimatorComponent::Update(const GameObject*)
	{
		m_Timer -= Game::dt;
		if (m_Timer <= 0)
		{
			if (char(m_pAnimation->frames.size()) <= ++m_FrameIndex) m_FrameIndex = 0;
			m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
			m_Timer += m_pAnimation->msPerFrame;
		}
	}
	void AnimatorComponent::SetFrame(const unsigned char frameIndex)
	{
		m_FrameIndex = frameIndex;
		m_Timer = m_pAnimation->msPerFrame;
		m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
	}
	void AnimatorComponent::SetAnimation(Animation* pAnimation)
	{
		m_pAnimation = pAnimation;
		SetFrame(0);
	}
	Animation* AnimatorComponent::GetpAnimation() const
	{
		return m_pAnimation;
	}
}