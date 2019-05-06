#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "ResourceManager.h"
#include "Minigin.h"

namespace e
{	//TODO FIX
	using namespace std;
	AnimationComponent::AnimationComponent(const std::string& animationName) :
		m_pTextureComponent{ nullptr },
		frameIndex{},
		timer{},
		pAnimation{ ResourceManager::GetInstance().GetpAnimation(animationName) }
	{
	}
	void AnimationComponent::WakeUp(const GameObject* pParent)
	{
		if (TextureComponent* pTextureComponent = pParent->GetpComponent<TextureComponent>())
		{
			m_pTextureComponent = pTextureComponent;
			//if ((m_pTextureComponent->isActive = !m_spTextures.empty())) m_pTextureComponent->SetTexture(m_spTextures.front(), false);
		}
		else throw runtime_error(string("Make sure TextComponent have a TextureComponent sibling!\n"));
	}
	void AnimationComponent::Update(const GameObject*)
	{
		timer -= Minigin::dt;
		if (timer < 0)
		{
			if (pAnimation->frames.size() <= ++frameIndex) frameIndex = 0;
			m_pTextureComponent->SetTexture(&pAnimation->frames[frameIndex], false);
			timer += pAnimation->msPerFrame;
		}
	}
}