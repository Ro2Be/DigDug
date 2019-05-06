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
		m_RendererFlip{ SDL_RendererFlip::SDL_FLIP_NONE }
	{
		Canvas::GetInstance().AddTextureComponent(this); //Let the canvas know it has to render this component
	}
	TextureComponent::TextureComponent(const string& textureName, const SDL_RendererFlip& flip) :
		m_pTransform{ nullptr },
		m_pTexture{ ResourceManager::GetInstance().GetpTexture(textureName) },
		m_RendererFlip{ flip }
	{
		Canvas::GetInstance().AddTextureComponent(this); //Let the canvas know it has to render this component
	}
	void TextureComponent::WakeUp(const GameObject* pParent)
	{
		m_pTransform = pParent->GetpComponent<TransformComponent>();
		if (m_pTransform == nullptr) throw runtime_error("TextureComponent needs a TransformComponent");
	}
	ExtraTexture* const TextureComponent::GetpTexture() const
	{
		return m_pTexture;
	}
	const SDL_RendererFlip& TextureComponent::GetRendererFlip() const
	{
		return m_RendererFlip;
	}
	const SPoint& TextureComponent::GetPosition() const
	{
		return m_pTransform->GetPosition();
	}
	const SVector & TextureComponent::GetSize() const
	{
		return m_pTransform->GetSize();
	}
	void TextureComponent::FlipHorizontal()
	{
		m_RendererFlip = SDL_RendererFlip(m_RendererFlip ^ SDL_FLIP_HORIZONTAL);
	}
	void TextureComponent::FlipVertical()
	{
		m_RendererFlip = SDL_RendererFlip(m_RendererFlip ^ SDL_FLIP_VERTICAL);
	}
	void TextureComponent::SetTexture(const string& textureName, bool adaptSize)
	{
		m_pTexture = ResourceManager::GetInstance().GetpTexture(textureName);
		if (adaptSize)
		{
			IVector size;
			SDL_QueryTexture(m_pTexture->pSDLTexture, nullptr, nullptr, &size.x, &size.y);
			m_pTransform->SetSize(short(size.x), short(size.y));
		}
	}
	void TextureComponent::SetTexture(ExtraTexture* pRuntimeTexture, bool adaptSize)
	{
		m_pTexture = pRuntimeTexture;
		if (adaptSize)
		{
			IVector size;
			SDL_QueryTexture(m_pTexture->pSDLTexture, nullptr, nullptr, &size.x, &size.y);
			m_pTransform->SetSize(short(size.x), short(size.y));
		}
	}
}