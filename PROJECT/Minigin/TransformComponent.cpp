#include "MiniginPCH.h"
#include "TransformComponent.h"

namespace e
{
	using namespace std;

	TransformComponent::TransformComponent(short x, short y, float scale) :
		pParent{ nullptr },
		position{ x, y },
		scale{ scale, scale }, 
		rotation{ 0 },
		flip{ Flip::o }
	{
	}
	TransformComponent::TransformComponent(const SPoint& position, float scale) :
		pParent{ nullptr },
		position{ position },
		scale{ scale, scale },
		rotation{ 0 },
		flip{ Flip::o }
	{
	}
	SPoint TransformComponent::GetWorldPosition() const
	{
		if (pParent)
		{
			const SPoint parentWorldPosition{ pParent->GetWorldPosition() };
			return { parentWorldPosition.x + (pParent->flip & Flip::x ? position.x : - position.x), parentWorldPosition.y + (pParent->flip & Flip::y ? position.y : -position.y) };
		}
		return position;
	}
	FVector TransformComponent::GetWorldScale() const
	{
		if (pParent)
		{
			const FVector parentWorldScale{ pParent->GetWorldScale() };
			//TODO KEEP TRACK OF ROTATION
			return { scale.x * parentWorldScale.x, scale.y * parentWorldScale.y };
		}
		return scale;
	}
	short TransformComponent::GetWorldRotation() const
	{
		if (pParent) return pParent->rotation + rotation; //TODO KEEP TRACK OF ROTATION
		return rotation;
	}
	Flip TransformComponent::GetWorldFlip() const
	{
		if (pParent) return pParent->flip; //TODO KEEP TRACK OF FLIP
		return flip;
	}
	void TransformComponent::ResetScale()
	{
		scale.x = 1.f;
		scale.y = 1.f;
	}
	void TransformComponent::Scale(const float& scalar)
	{
		scale *= scalar;
	}
	void TransformComponent::Scale(const FVector& scalars)
	{
		scale.x *= scalars.x;
		scale.y *= scalars.y;
	}
	Command* TransformComponent::CreateMoveCommand(const SVector& movement)
	{
		return new MoveCommand(this, movement);
	}
}