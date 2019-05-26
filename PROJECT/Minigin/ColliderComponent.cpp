#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "TextureComponent.h"
namespace e
{
	using namespace std;

	std::unordered_map<std::string, std::vector<ColliderComponent*>> ColliderComponent::ColliderGroupsByName{};

	ColliderComponent::ColliderComponent(const std::string& colliderGroup)
	{	
		//Add colliderComponent to colliderGroup
		ColliderGroupsByName[colliderGroup].push_back(this);
	}
	ColliderComponent::~ColliderComponent()
	{	
		//Remove colliderComponent from colliderGroup
		for (pair<string, vector<ColliderComponent*>> colliderGroup : ColliderGroupsByName) experimental::erase(colliderGroup.second, this);
	}
	void ColliderComponent::WakeUp(const GameObject* pParent)
	{
		m_pGameObject = pParent;
		m_pTransformComponent = pParent->GetpComponent<TransformComponent>("Missing dependency: ColliderComponent needs a TransformComponent sibling!");
		m_TopLeft = SVector{ 0, 0 }; //TODO FIX
		m_BottomRight = SVector{ short(pParent->GetpComponent<TextureComponent>()->GetFrame().source.w), short(pParent->GetpComponent<TextureComponent>()->GetFrame().source.h) }; //TODO FIX
	}
	void ColliderComponent::Update(const GameObject*)
	{
		/*empty*/
	}
	const GameObject* ColliderComponent::GetpGameObject() const
	{
		return m_pGameObject;
	}
	void ColliderComponent::HandleCollision(CollisionHandler* collisionHandler, const std::string& colliderGroup) const
	{
		for (ColliderComponent* pColliderComponent : ColliderGroupsByName[colliderGroup])
		{
			if (IsCollision(this, pColliderComponent)) collisionHandler->HandleCollision(m_pGameObject, pColliderComponent->GetpGameObject());
		}
	}
	SPoint ColliderComponent::GetTopLeft() const
	{
		return m_pTransformComponent->position + m_TopLeft;
	}
	SPoint ColliderComponent::GetBottomRight() const
	{
		return SPoint{ m_pTransformComponent->position.x + short(float(m_BottomRight.x) * m_pTransformComponent->scale.x), m_pTransformComponent->position.y + short(float(m_BottomRight.y) * m_pTransformComponent->scale.y) };
	}
	bool ColliderComponent::IsCollision(const ColliderComponent* pColliderComponent0, const ColliderComponent* pColliderComponent1)
	{
		return pColliderComponent0->GetTopLeft().x <= pColliderComponent1->GetBottomRight().x 
			&& pColliderComponent0->GetTopLeft().y <= pColliderComponent1->GetBottomRight().y
			&& pColliderComponent1->GetTopLeft().x <= pColliderComponent0->GetBottomRight().x 
			&& pColliderComponent1->GetTopLeft().y <= pColliderComponent0->GetBottomRight().y;
	}
}
