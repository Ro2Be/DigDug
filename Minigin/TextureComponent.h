#pragma once
#include <SDL.h>

namespace e 
{
	class TransformComponent;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent();
		TextureComponent(const std::string& textureName, const SDL_RendererFlip& flip = SDL_FLIP_NONE);
		~TextureComponent() override = default;
		//WAKEUP
		void WakeUp(const GameObject* pParent) override;
		//GET
		const SPoint& GetPosition() const;
		const SVector& GetSize() const;
		ExtraTexture* const GetpTexture() const;
		const SDL_RendererFlip& GetRendererFlip() const;
		//SET
		void FlipHorizontal();
		void FlipVertical();
		void SetTexture(const std::string& textureName, bool adaptSize = true);
		void SetTexture(ExtraTexture* pRuntimeTexture, bool adaptSize = true);
	private:
		TransformComponent* m_pTransform;
		ExtraTexture* m_pTexture;
		SDL_RendererFlip m_RendererFlip;
	};
}