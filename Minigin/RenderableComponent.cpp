#include "MiniginPCH.h"
#include "RenderableComponent.h"
#include "ResourceManager.h"
#include "Canvas.h"

namespace e
{
	using namespace std;
	RenderableComponent::RenderableComponent() :
		m_pTransformComponent{ nullptr },
		m_pTexture{ nullptr }
	{
		Canvas::GetInstance().AddRenderableComponent(this); //Let the canvas know it has to render this component
	}
	RenderableComponent::RenderableComponent(const std::string& textureName) :
		m_pTransformComponent{ nullptr },
		m_pTexture{ ResourceManager::GetInstance().GetSDLTexture(textureName) }
	{
		Canvas::GetInstance().AddRenderableComponent(this); //Let the canvas know it has to render this component
	}
	void RenderableComponent::WakeUp(const GameObject* pParent)
	{
		m_pTransformComponent = pParent->GetpComponent<TransformComponent>("RenderableComponent(texture/tilemap) needs a TransformComponent");
	}
	const SPoint& RenderableComponent::GetPosition() const
	{
		return m_pTransformComponent->position;
	}
	void RenderableComponent::DestroyTexture() const
	{
		if (m_pTexture) SDL_DestroyTexture(m_pTexture);
	}
}
