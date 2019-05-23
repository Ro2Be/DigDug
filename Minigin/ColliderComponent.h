#pragma once
#include "TransformComponent.h"
#include <unordered_map>
namespace e
{
	class CollisionHandler abstract
	{
	public:
		virtual ~CollisionHandler() = default;
		virtual void HandleCollision(const e::GameObject* pGameObject, const GameObject* pOtherGameObject) = 0;
	};

	class ColliderComponent final : public Component
	{
	public:
		explicit ColliderComponent(const std::string& colliderGroup);
		virtual ~ColliderComponent() override;
		virtual void WakeUp(const GameObject* pParent) override;
		virtual void Update(const GameObject*) override;
		const GameObject* GetpGameObject() const;
		void HandleCollision(CollisionHandler* collisionHandler, const std::string& colliderGroup) const;
		SPoint GetTopLeft() const;
		SPoint GetBottomRight() const;
	private:
		const GameObject* m_pGameObject;
		TransformComponent* m_pTransformComponent{};
		SVector m_TopLeft{};		//relative to transform component
		SVector m_BottomRight{};	//relative to transform component

		static std::unordered_map<std::string, std::vector<ColliderComponent*>> ColliderGroupsByName;
		static bool IsCollision(const ColliderComponent* pColliderComponent0,
		                        const ColliderComponent* pColliderComponent1);
	};
}
