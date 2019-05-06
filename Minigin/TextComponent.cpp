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
		m_spFont{ ResourceManager::GetInstance().LoadFont(fontName, fontSize) },
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
		m_spFont = ResourceManager::GetInstance().LoadFont(fontName, fontSize);
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
		m_pTextureComponent->SetTexture(m_spFont->GetpTexture(m_Text, m_Color));
	}
}