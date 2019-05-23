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
		m_pTextureComponent = pParent->GetpComponent<TextureComponent>("Make sure each TextComponent has a TextureComponent sibling!");
		m_pTextureComponent->SetFrame(m_pAnimations[m_AnimationIndex]->frames[m_FrameIndex], false);
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
	void AnimatorComponent::FlipHorizontal() const
	{
		//TODO WHY IS THIS HERE
	}
	void AnimatorComponent::FlipVertical() const
	{
		//TODO WHY IS THIS HERE
	}
	void AnimatorComponent::SetFrame(const unsigned char frameIndex)
	{
		m_FrameIndex = frameIndex;
		m_Timer = m_pAnimations[m_AnimationIndex]->msPerFrame;
		m_pTextureComponent->SetFrame(m_pAnimations[m_AnimationIndex]->frames[m_FrameIndex], false);
	}
	void AnimatorComponent::SetAnimation(const unsigned char animationIndex)
	{
		m_AnimationIndex = animationIndex;
		SetFrame(0);
	}
	Animation* AnimatorComponent::GetpAnimation() const
	{
		return m_pAnimations[m_AnimationIndex];
	}
}