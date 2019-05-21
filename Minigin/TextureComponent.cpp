#include "MiniginPCH.h"
#include "Components.h"
#include "ResourceManager.h"
#include "Canvas.h"
#include "TransformComponent.h"

namespace e
{
	using namespace std;
	TextureComponent::TextureComponent():
		RenderableComponent(),
		m_Frame{},
		m_Flip{ SDL_FLIP_NONE }
	{
		
	}
	TextureComponent::TextureComponent(const string& textureName, const SDL_RendererFlip& flip) :
		RenderableComponent(textureName),
		m_Frame{ ResourceManager::GetInstance().GetFrame(textureName) },
		m_Flip{ flip }
	{
	}
	SVector TextureComponent::GetSize() const
	{
		return { short(float(m_Frame.source.w) * m_pTransformComponent->scale.x), short(float(m_Frame.source.h) * m_pTransformComponent->scale.y) };
	}
	const Frame& TextureComponent::GetFrame() const
	{
		return m_Frame;
	}
	void TextureComponent::SetTexture(SDL_Texture* texture, bool adaptSize)
	{
		m_pTexture = texture;
		if (adaptSize)
		{
			SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_Frame.source.w, &m_Frame.source.h);
			m_Frame.center = { m_Frame.source.w / 2, m_Frame.source.h / 2 };
			m_pTransformComponent->ResetScale();
		}
	}
	void TextureComponent::SetFrame(const Frame& frame, bool adaptSize)
	{
		m_Frame = frame;
		if (adaptSize) m_pTransformComponent->ResetScale();
	}
	void TextureComponent::Draw(SDL_Renderer* pRenderer) const
	{
		const SVector size{ GetSize() };
		SDL_Rect destination;
		destination.x = m_pTransformComponent->position.x;
		destination.y = m_pTransformComponent->position.y;
		destination.w = int(float(m_Frame.source.w) * m_pTransformComponent->scale.x);
		destination.h = int(float(m_Frame.source.h) * m_pTransformComponent->scale.y);
		SDL_RenderCopyEx(pRenderer, m_pTexture, &m_Frame.source, &destination, m_pTransformComponent->rotation, &m_Frame.center, SDL_RendererFlip(m_pTransformComponent->flip));
	}
}