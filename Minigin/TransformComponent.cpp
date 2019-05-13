#include "MiniginPCH.h"
#include "TransformComponent.h"

namespace e
{
	using namespace std;

	TransformComponent::TransformComponent(short x, short y, float scale) :
		m_Position{ x, y },
		m_Depth{ .5f },
		m_Scale{ scale, scale }, 
		m_Rotation{ 0.f }
	{
	}
	TransformComponent::TransformComponent(const SPoint& position, float scale) :
		m_Position{ position },
		m_Depth{ .5f },
		m_Scale{ scale, scale },
		m_Rotation{ 0.f }
	{
	}
	void TransformComponent::SetPosition(short x, short y)
	{
		m_Position.x = x;
		m_Position.y = y;
	}
	void TransformComponent::SetPosition(const SPoint& position)
	{
		m_Position = position;
	}
	void TransformComponent::AddMovement(short x, short y)
	{
		m_Position.x += x;
		m_Position.y += y;
	}
	void TransformComponent::AddMovement(const SVector& movement)
	{
		m_Position += movement;
	}
	void TransformComponent::ResetScale()
	{
		m_Scale.x = 1.f;
		m_Scale.y = 1.f;
	}
	void TransformComponent::SetScale(const FVector& scale)
	{
		m_Scale = scale;
	}
	void TransformComponent::Scale(const float& scale)
	{
		m_Scale *= scale;
	}
	void TransformComponent::Scale(const FVector& scale)
	{
		m_Scale.x *= scale.x;
		m_Scale.y *= scale.y;
	}
	const SPoint& TransformComponent::GetPosition() const
	{
		return m_Position;
	}
	const FVector& TransformComponent::GetScale() const
	{
		return m_Scale;
	}
	Command* TransformComponent::CreateMoveCommand(const SVector& movement)
	{
		return new CommandMove(this, movement);
	}
}