#pragma once
#include "Component.h"

namespace e
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(short x, short y, short w, short h);
		TransformComponent(const SPoint& position, const SVector& size);
		void SetPosition(short x, short y);
		void SetPosition(const SPoint& position);
		void SetSize(short x, short y);
		void SetSize(const SVector& position);
		const SPoint& GetPosition() const;
		const SVector& GetSize() const;
	private:
		SPoint m_Position;
		SVector m_Size;
		float m_Depth;
	};
}