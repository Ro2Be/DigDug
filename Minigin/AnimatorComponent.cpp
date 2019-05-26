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
		m_Timer{ 0 },
		m_Loop{ true },
		m_Lock{ false }
	{
	}
	AnimatorComponent::AnimatorComponent(const std::string& animation) :
		m_pTextureComponent{ nullptr },
		m_FrameIndex{ 0 },
		m_pAnimation{ ResourceManager::GetInstance().GetpAnimation(move(animation)) },
		m_Timer{ m_pAnimation->msPerFrame },
		m_Loop{ true },
		m_Lock{ false }
	{
	}
	void AnimatorComponent::WakeUp(const GameObject* pParent)
	{
		m_pTextureComponent = pParent->GetpComponent<TextureComponent>("Make sure each TextComponent has a TextureComponent sibling!");
		if (m_pAnimation) m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
	}
	void AnimatorComponent::Update(const GameObject*)
	{
		if (m_pAnimation)
		{
			if (m_FrameIndex < unsigned char(m_pAnimation->frames.size()))
			{
				m_Timer -= Game::dt;
				if (m_Timer <= 0)
				{
					m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
					m_Timer += m_pAnimation->msPerFrame;
					if (unsigned char(m_pAnimation->frames.size() <= ++m_FrameIndex))
					{
						if (m_Loop) m_FrameIndex = 0;
					}
				}
			}
		}
	}
	bool AnimatorComponent::GetEndOfAnimation() const
	{
		return unsigned char(m_pAnimation->frames.size()) == m_FrameIndex;
	}
	void AnimatorComponent::SetLock(bool lock)
	{
		m_Lock = lock;
	}
	void AnimatorComponent::SetFrame(const unsigned char frameIndex, bool loop)
	{
		if (!m_Lock)
		{
			m_FrameIndex = frameIndex;
			m_Loop = loop;
			m_Timer = m_pAnimation->msPerFrame;
			m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
		}
	}
	void AnimatorComponent::SetAnimation(Animation* pAnimation, bool loop)
	{
		if (!m_Lock)
		{
			m_pAnimation = pAnimation;
			SetFrame(0, loop);
		}
	}
	Animation* AnimatorComponent::GetpAnimation() const
	{
		return m_pAnimation;
	}
}