#include "MiniginPCH.h"
#include "TransformComponent.h"

namespace e
{
	using namespace std;

	TransformComponent::TransformComponent(short x, short y, short w, short h) :
		m_Position{ x, y },
		m_Size{ w, h },
		m_Depth{ 0.5f }
	{
	}
	TransformComponent::TransformComponent(const SPoint& position, const SVector& size) :
		m_Position{ position },
		m_Size{ size },
		m_Depth{ 0.5f }
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
	void TransformComponent::SetSize(short x, short y)
	{
		m_Size.x = x;
		m_Size.y = y;
	}
	void TransformComponent::SetSize(const SVector& v)
	{
		m_Size = v;
	}
	const SPoint& TransformComponent::GetPosition() const
	{
		return m_Position;
	}
	const SVector & TransformComponent::GetSize() const
	{
		return m_Size;
	}
}