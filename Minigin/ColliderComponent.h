#pragma once
#include "TransformComponent.h"
#include <unordered_map>
namespace e
{
	class ColliderComponent;

	class CollisionHandler
	{
	public:
		virtual ~CollisionHandler() = default;
		virtual void HandleCollision(const GameObject* pOtherGameObject) = 0;
	};

	class ColliderComponent : public Component
	{
	public:
		explicit ColliderComponent(const std::string& colliderGroup);
		virtual ~ColliderComponent() override;
		virtual void WakeUp(const GameObject* pParent) override;
		const GameObject* GetpGameObject() const;
		void HandleCollision(const std::string& colliderGroup, CollisionHandler*) const;
		SPoint GetTopLeft() const;
		SPoint GetBottomRight() const;
	private:
		const GameObject* m_pGameObject;
		TransformComponent* m_pTransformComponent{};
		SVector m_TopLeft{};		//relative to transform component
		SVector m_BottomRight{};	//relative to transform component

		static std::unordered_map<std::string, std::vector<ColliderComponent*>> ColliderGroupsByName;
		static bool IsCollision(const ColliderComponent* pColliderComponent0, const ColliderComponent* pColliderComponent1)
		{
			return pColliderComponent0->GetTopLeft().x <= pColliderComponent1->GetBottomRight().x && pColliderComponent0->GetTopLeft().y <= pColliderComponent1->GetBottomRight().y
				&& pColliderComponent1->GetTopLeft().x <= pColliderComponent0->GetBottomRight().x && pColliderComponent1->GetTopLeft().y <= pColliderComponent0->GetBottomRight().y;
		}
	};
}
