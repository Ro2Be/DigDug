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
	void Canvas::AddRenderableComponent(RenderableComponent* pTextureComponent)
	{
		m_pRenderableComponents.push_back(pTextureComponent);
	}
	void Canvas::Render()
	{
		SDL_RenderClear(m_pRenderer);
		experimental::erase(m_pRenderableComponents, nullptr); //TODO: Add check if gameobject was deleted OR don't do this every frame
		for (RenderableComponent* pRenderableComponent : m_pRenderableComponents) if (pRenderableComponent->isActive) pRenderableComponent->Draw(m_pRenderer);
		SDL_RenderPresent(m_pRenderer);
	}
	void Canvas::Destroy()
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}
	SDL_Renderer* Canvas::GetpRenderer() const
	{
		return m_pRenderer;
	}
}