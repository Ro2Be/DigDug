#pragma once
namespace e
{
	class GameObject;
	class Component abstract
	{
	public:
		virtual ~Component() = default;
		virtual void WakeUp(const GameObject*){};
		virtual void Update(const GameObject*){};
		bool isActive{ true };
	};
}
