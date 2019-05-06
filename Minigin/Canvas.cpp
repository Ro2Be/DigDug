#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Canvas.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include <experimental/vector>

namespace e
{
	using namespace std;
	
	void Canvas::Init(const string& title, const SVector& resolution)
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

		m_pWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resolution.x, resolution.y, SDL_WINDOW_OPENGL);
		if (m_pWindow == nullptr) throw runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_pRenderer == nullptr) throw runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
	void Canvas::AddTextureComponent(TextureComponent* pTextureComponent)
	{
		m_pTextureComponents.push_back(pTextureComponent);
	}
	void Canvas::Render()
	{
		SDL_RenderClear(m_pRenderer);
		//TODO: Add check if gameobject was deleted OR don't do this every frame
		experimental::erase_if(m_pTextureComponents, [](TextureComponent* pTC) { return pTC == nullptr; });
		for (TextureComponent* pTextureComponent : m_pTextureComponents)
		{
			if (pTextureComponent->isActive)
			{
				if (ExtraTexture* const pTexture = pTextureComponent->GetpTexture()) //TODO REMOVE IF, isActive should be false
				{
					SDL_Rect dst;
					dst.x = pTextureComponent->GetPosition().x;
					dst.y = pTextureComponent->GetPosition().y;
					dst.w = pTextureComponent->GetSize().x;
					dst.h = pTextureComponent->GetSize().y;
					pTexture->RenderCopy(m_pRenderer, dst, pTextureComponent->GetRendererFlip());
				}
			}
		}
		while (m_pTextureComponents.back() == nullptr) m_pTextureComponents.pop_back();
		SDL_RenderPresent(m_pRenderer);
	}
	void Canvas::Destroy()
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}
	SDL_Renderer * Canvas::GetpRenderer()
	{
		return m_pRenderer;
	}
}