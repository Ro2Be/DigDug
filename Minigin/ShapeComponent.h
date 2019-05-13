#pragma once
#include "Shape.h"

namespace e
{
	class ShapeComponent
	{
	public:
		ShapeComponent();

	private:
		const GameObject* pParent;
		std::vector<Shape*> m_pShapes;
	};
}