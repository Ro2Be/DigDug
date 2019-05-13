#pragma once
#include "Structs.h"

namespace e
{
	class Shape{};

	class SquareShape : public Shape
	{
	public:
	private:
		SVector m_TopLeft;
		SVector m_BottomRight;
	};
}