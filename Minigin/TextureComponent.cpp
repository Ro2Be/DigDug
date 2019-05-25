#include "MiniginPCH.h"
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
		SDL_Rect destination;
		const SPoint worldPosition{ m_pTransformComponent->GetWorldPosition() };
		destination.x = worldPosition.x;
		destination.y = worldPosition.y;
		const FVector worldScale{ m_pTransformComponent->GetWorldScale() };
		destination.w = int(float(m_Frame.source.w) * worldScale.x);
		destination.h = int(float(m_Frame.source.h) * worldScale.y);
		SDL_RenderCopyEx(pRenderer, m_pTexture, &m_Frame.source, &destination, m_pTransformComponent->GetWorldRotation(), &m_Frame.center, SDL_RendererFlip(m_pTransformComponent->GetWorldFlip()));
	}
}