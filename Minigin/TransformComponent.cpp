#include "MiniginPCH.h"
#include "TransformComponent.h"

namespace e
{
	using namespace std;

	TransformComponent::TransformComponent(short x, short y, float scale) :
		position{ x, y },
		scale{ scale, scale }, 
		rotation{ 0 },
		flip{ Flip::o }
	{
	}
	TransformComponent::TransformComponent(const SPoint& position, float scale) :
		position{ position },
		scale{ scale, scale },
		rotation{ 0 },
		flip{ Flip::o }
	{
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