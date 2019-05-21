#include "MiniginPCH.h"
#include "AnimatorComponent.h"
#include "ResourceManager.h"
#include "Game.h"

namespace e
{
	using namespace std;
	AnimatorComponent::AnimatorComponent(const std::string& animation) :
		m_pTextureComponent{ nullptr },
		m_FrameIndex{ 0 },
		m_AnimationIndex{ 0 },
		m_pAnimations{ 1 },
		m_Timer{}
	{
		m_pAnimations[0] = ResourceManager::GetInstance().GetpAnimation(move(animation));
		m_Timer = m_pAnimations[m_AnimationIndex]->msPerFrame;
	}
	AnimatorComponent::AnimatorComponent(const std::vector<std::string>& animations) :
		m_pTextureComponent{ nullptr },
		m_FrameIndex{ 0 },
		m_AnimationIndex{ 0 },
		m_pAnimations{ animations.size() },
		m_Timer{ 0 }
	{
		for (int i{}; i < m_pAnimations.size(); ++i) m_pAnimations[i] = ResourceManager::GetInstance().GetpAnimation(move(animations[i]));
		m_Timer = m_pAnimations[m_AnimationIndex]->msPerFrame;
	}
	void AnimatorComponent::WakeUp(const GameObject* pParent)
	{
		if (TextureComponent* pTextureComponent = pParent->GetpComponent<TextureComponent>())
		{
			m_pTextureComponent = pTextureComponent;
			m_pTextureComponent->SetFrame(m_pAnimations[m_AnimationIndex]->frames[m_FrameIndex], false);
		}
		else throw runtime_error(string("Make sure each TextComponent has a TextureComponent sibling!"));
	}
	void AnimatorComponent::Update(const GameObject*)
	{
		m_Timer -= Game::dt;
		if (m_Timer <= 0)
		{
			if (char(m_pAnimations[m_AnimationIndex]->frames.size()) <= ++m_FrameIndex) m_FrameIndex = 0;
			m_pTextureComponent->SetFrame(m_pAnimations[m_AnimationIndex]->frames[m_FrameIndex], false);
			m_Timer += m_pAnimations[m_AnimationIndex]->msPerFrame;
		}
	}
	void AnimatorComponent::SetFrame(const unsigned char frameIndex)
	{
		m_FrameIndex = frameIndex;
		m_pTextureComponent->SetFrame(m_pAnimations[m_AnimationIndex]->frames[m_FrameIndex], false);
	}
	void AnimatorComponent::SetAnimation(const unsigned char animationIndex)
	{
		m_AnimationIndex = animationIndex;
		SetFrame(0);
	}
}