#pragma once
namespace e
{
	class GameObject;
	class Component
	{
	public:
		virtual ~Component(){};
		virtual void WakeUp(const GameObject*){};
		virtual void Update(const GameObject*){};
		bool isActive{ true };
	};
}
