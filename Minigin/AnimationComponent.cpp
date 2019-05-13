#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "ResourceManager.h"
#include "Game.h"

namespace e
{	//TODO FIX
	using namespace std;
	AnimationComponent::AnimationComponent(const std::string& animationName) :
		m_pTextureComponent{ nullptr },
		m_FrameIndex{ 0 },
		m_Timer{},
		m_pAnimation{ ResourceManager::GetInstance().GetpAnimation(animationName) }
	{
	}
	void AnimationComponent::WakeUp(const GameObject* pParent)
	{
		if (TextureComponent* pTextureComponent = pParent->GetpComponent<TextureComponent>())
		{
			m_pTextureComponent = pTextureComponent;
			m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
		}
		else throw runtime_error(string("Make sure each TextComponent has a TextureComponent sibling!"));
	}
	void AnimationComponent::Update(const GameObject*)
	{
		m_Timer -= Game::dt;
		if (m_Timer < 0)
		{
			if (char(m_pAnimation->frames.size()) <= ++m_FrameIndex) m_FrameIndex = 0;
			m_pTextureComponent->SetFrame(m_pAnimation->frames[m_FrameIndex], false);
			m_Timer += m_pAnimation->msPerFrame;
		}
	}
}