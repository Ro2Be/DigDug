#pragma once
#include <SDL.h>
#include "RenderableComponent.h"
namespace e 
{
	class TransformComponent;
	class TextureComponent final : public RenderableComponent
	{
	public:
		TextureComponent();
		explicit TextureComponent(const std::string& textureName, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
		~TextureComponent() override = default;
		//DRAW
		virtual void Draw(SDL_Renderer* pRenderer) const override;
		//GET
		SVector GetSize() const;
		const Frame& GetFrame() const;
		//SET
		void SetFrame(const Frame& frame, bool adaptSize = true);
		void SetTexture(SDL_Texture* texture, bool adaptSize = true);
	private:

		Frame m_Frame;
		SDL_RendererFlip m_Flip;
	};
}
