#pragma once
#include <SDL.h>

namespace e 
{
	class TransformComponent;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent();
		explicit TextureComponent(const std::string& textureName, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
		~TextureComponent() override = default;
		//WAKEUP
		void WakeUp(const GameObject* pParent) override;
		//DRAW
		void Draw(SDL_Renderer* pRenderer) const;
		//GET
		const SPoint& GetPosition() const;
		SVector GetSize() const;
		SDL_Texture*& GetpSDLTexture();
		Frame& GetFrameRef();
		//SET
		void FlipHorizontal();
		void FlipVertical();
		void SetTexture(SDL_Texture* texture, bool adaptSize = true);
		void SetFrame(const Frame& frame, bool adaptSize = true);
	private:
		TransformComponent* m_pTransform;
		SDL_Texture* m_pTexture;
		Frame m_Frame;
		SDL_RendererFlip m_Flip;
	};
}