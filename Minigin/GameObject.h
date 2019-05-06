#pragma once
#include <map>
namespace e
{
	class Component;
	class GameObject final
	{
	public:
		//GameObject() = default;
		explicit GameObject(const std::vector<Component*>& pComponents);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void WakeUp();
		void Update();
		void Add(Component* pC);

	private:
		std::vector<Component*> m_pComponents;

	public:
		template<class T>
		T* GetpComponent() const
		{
			for (Component* pC : m_pComponents)
			{
				if (T* pT{ dynamic_cast<T*>(pC) }) return pT;
			}
			return nullptr;
		}
	};
}
