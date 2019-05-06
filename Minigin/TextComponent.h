#pragma once
#include "TextureComponent.h"
#include "Font.h"
#include <SDL.h>

namespace e
{
	class TextComponent final : public Component
	{
	public:
		TextComponent(const std::string& text, const std::string& fontName, unsigned fontSize, const SDL_Color& color = { 255,255,255 });
		void WakeUp(const GameObject* pParent) override;
		void SetFont(const std::string& fontName, const unsigned fontSize);
		void SetColor(const SDL_Color& color);
		void SetText(const std::string& text);
	private:
		void SetTexture() const;
		TextureComponent* m_pTextureComponent;
		std::string m_Text;
		std::shared_ptr<Font> m_spFont;
		SDL_Color m_Color;
	};
}