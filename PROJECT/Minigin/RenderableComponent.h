#pragma once
#include "Component.h"
#include "TransformComponent.h"
namespace e
{
	class RenderableComponent : public Component
	{
	public:
		RenderableComponent();
		explicit RenderableComponent(const std::string& textureName);
		virtual ~RenderableComponent() override = default;
		//WAKEUP
		void WakeUp(const GameObject* pParent) override;
		//DRAW
		virtual void Draw(SDL_Renderer* pRenderer) const = 0;
		//GET
		const SPoint& GetPosition() const;
		//SET
		void DestroyTexture() const;
	protected:
		TransformComponent* m_pTransformComponent;
		SDL_Texture* m_pTexture;
	};
}
