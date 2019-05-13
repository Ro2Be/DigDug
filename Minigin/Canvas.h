#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "TextureComponent.h"

struct SDL_Window;
struct SDL_Renderer;

namespace e
{
	struct ExtraTexture;
	class Canvas final : public Singleton<Canvas>
	{
	public:
		void Init(const std::string& title, const SVector& resolution);
		void AddTextureComponent(TextureComponent* pTextureComponent);
		void Render();
		void Destroy();
		SDL_Renderer* GetpRenderer() const;
	private:
		SDL_Window* m_pWindow{ nullptr };
		SDL_Renderer* m_pRenderer{ nullptr };
		//std::unordered_map<SDL_Texture*, std::vector<Frame>> m_TexturesBySDLTexture;
		std::vector<TextureComponent*> m_pTextureComponents;
	};
}