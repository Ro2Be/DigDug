#include "MiniginPCH.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "Canvas.h"

namespace e
{
	using namespace std;

	TextComponent::TextComponent(const string& text, const string& fontName, const unsigned fontSize, const SDL_Color& color) :
		m_pTextureComponent{ nullptr },
		m_Text{ text },
		m_pFont{ ResourceManager::GetInstance().LoadpTTFFont(fontName, fontSize) },
		m_Color{ color }
	{
	}
	void TextComponent::WakeUp(const GameObject* pParent)
	{
		if (TextureComponent* pTextureComponent = pParent->GetpComponent<TextureComponent>())
		{
			m_pTextureComponent = pTextureComponent;
			if ((m_pTextureComponent->isActive = !m_Text.empty())) SetTexture();
		}
		else throw runtime_error(string("Make sure TextComponent have a TextureComponent sibling!\n"));
	}
	void TextComponent::SetFont(const std::string& fontName, const unsigned fontSize)
	{
		m_pFont = ResourceManager::GetInstance().LoadpTTFFont(fontName, fontSize);
		SetTexture();
	}
	void TextComponent::SetColor(const SDL_Color& color)
	{
		m_Color = color;
		SetTexture();
	}
	void TextComponent::SetText(const string& text)
	{
		m_Text = text;
		if ((m_pTextureComponent->isActive = !m_Text.empty())) SetTexture();
	}
	void TextComponent::SetTexture() const
	{
		if (SDL_Surface* pSurface = TTF_RenderText_Blended(m_pFont, m_Text.c_str(), m_Color))
		{
			if (SDL_Texture* pSDLTexture = SDL_CreateTextureFromSurface(Canvas::GetInstance().GetpRenderer(), pSurface))
			{
				SDL_FreeSurface(pSurface); //FREE THE SURFACE
				if (SDL_Texture* pTexture = m_pTextureComponent->GetpSDLTexture()) SDL_DestroyTexture(pTexture); //DESTROY PREVIOUS SDL_TEXTURE
				m_pTextureComponent->SetTexture(pSDLTexture); //SET THE TEXTURE
			}
			else throw runtime_error(string("Failed to create texture from surface: ") + SDL_GetError());
		}
		else throw runtime_error(string("Render text failed: ") + SDL_GetError());
	}
}