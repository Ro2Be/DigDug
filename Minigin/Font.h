#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include "Structs.h"

namespace e
{
	class Font
	{
	public:
		TTF_Font* GetFont() const;
		explicit Font(const std::string& name, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;

		ExtraTexture* GetpTexture(const std::string& text, const SDL_Color& color);
	private:
		TTF_Font* m_Font;
		unsigned int m_Size;
		ExtraTexture m_Texture;
	};
}