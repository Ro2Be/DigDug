#include "MiniginPCH.h"
#include "Font.h"
#include "Structs.h"
#include "Canvas.h"

namespace e
{
	using namespace std;

	TTF_Font* Font::GetFont() const { return m_Font; }

	Font::Font(const std::string & path, unsigned int size) :
		m_Font(nullptr),
		m_Size(size),
		m_Texture{ nullptr, {}, {} }
	{
		m_Font = TTF_OpenFont(path.c_str(), size);
		if (m_Font == nullptr)
		{
			throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
		}
	}

	Font::~Font()
	{
		TTF_CloseFont(m_Font);
	}

	ExtraTexture* e::Font::GetpTexture(const std::string & text, const SDL_Color & color)
	{

		if (SDL_Surface* pSurface = TTF_RenderText_Blended(m_Font, text.c_str(), color))
		{
			if (SDL_Texture* pSDLTexture = SDL_CreateTextureFromSurface(Canvas::GetInstance().GetpRenderer(), pSurface))
			{
				SDL_FreeSurface(pSurface);																				//FREE THE SURFACE
				if (m_Texture.pSDLTexture) SDL_DestroyTexture(m_Texture.pSDLTexture);									//DESTROY PREVIOUS SDLTEXTURE
				m_Texture.pSDLTexture = pSDLTexture;																	//SET PTEXTURE
				SDL_QueryTexture(m_Texture.pSDLTexture, nullptr, nullptr, &m_Texture.source.w, &m_Texture.source.h);	//SET SOURCE
				m_Texture.center = { m_Texture.source.w / 2, m_Texture.source.h / 2 };									//SET CENTER
				return &m_Texture;																						//RETURN TEXTURE
			}
			throw runtime_error(string("Failed to create texture from surface: ") + SDL_GetError());
		}
		throw runtime_error(string("Render text failed: ") + SDL_GetError());
	}
}