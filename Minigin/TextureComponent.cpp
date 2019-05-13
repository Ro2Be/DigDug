#include "MiniginPCH.h"
#include "Components.h"
#include "ResourceManager.h"
#include "Canvas.h"
#include "TransformComponent.h"

namespace e
{
	using namespace std;
	TextureComponent::TextureComponent():
		m_pTransform{ nullptr },
		m_pTexture{ nullptr },
		m_Frame{}
	{
		Canvas::GetInstance().AddTextureComponent(this); //Let the canvas know it has to render this component
	}
	TextureComponent::TextureComponent(const string& textureName, const SDL_RendererFlip& flip) :
		m_pTransform{ nullptr },
		m_pTexture{ ResourceManager::GetInstance().GetSDLTexture(textureName) },
		m_Frame{ ResourceManager::GetInstance().GetFrame(textureName) },
		m_Flip{ flip }
	{
		Canvas::GetInstance().AddTextureComponent(this); //Let the canvas know it has to render this component
	}
	void TextureComponent::WakeUp(const GameObject* pParent)
	{
		m_pTransform = pParent->GetpComponent<TransformComponent>();
		if (m_pTransform == nullptr) throw runtime_error("TextureComponent needs a TransformComponent");
	}
	const SPoint& TextureComponent::GetPosition() const
	{
		return m_pTransform->GetPosition();
	}
	SVector TextureComponent::GetSize() const
	{
		return { short(float(m_Frame.source.w) * m_pTransform->GetScale().x), short(float(m_Frame.source.h) * m_pTransform->GetScale().y) };
	}
	Frame& TextureComponent::GetFrameRef()
	{
		return m_Frame;
	}
	SDL_Texture*& TextureComponent::GetpSDLTexture()
	{
		return m_pTexture;
	}
	void TextureComponent::FlipHorizontal()
	{
		m_Flip = SDL_RendererFlip(m_Flip ^ SDL_FLIP_HORIZONTAL);
	}
	void TextureComponent::FlipVertical()
	{
		m_Flip = SDL_RendererFlip(m_Flip ^ SDL_FLIP_VERTICAL);
	}
	void TextureComponent::SetTexture(SDL_Texture* texture, bool adaptSize)
	{
		m_pTexture = texture;
		if (adaptSize)
		{
			SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_Frame.source.w, &m_Frame.source.h);
			m_Frame.center = { m_Frame.source.w / 2, m_Frame.source.h / 2 };
			m_pTransform->ResetScale();
		}
	}
	void TextureComponent::SetFrame(const Frame& frame, bool adaptSize)
	{
		m_Frame = frame;
		if (adaptSize) m_pTransform->ResetScale();
	}
	void TextureComponent::Draw(SDL_Renderer* pRenderer) const
	{
		const SPoint position{ GetPosition() };
		const SVector size{ GetSize() };
		SDL_Rect destination;
		destination.x = position.x;
		destination.y = position.y;
		destination.w = size.x;
		destination.h = size.y;
		SDL_RenderCopyEx(pRenderer, m_pTexture, &m_Frame.source, &destination, NULL, &m_Frame.center, m_Flip);
	}
}