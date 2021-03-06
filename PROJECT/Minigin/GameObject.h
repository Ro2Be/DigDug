#pragma once
#include "Component.h"

namespace e
{
	class Component;
	class GameObject final
	{
	public:
		//GameObject() = default;
		GameObject(const std::vector<Component*>& pComponents);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other);
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void WakeUp();
		void Update();

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
		template<class T>
		T* GetpComponent(const std::string& errorMessage) const
		{
			for (Component* pC : m_pComponents)
			{
				if (T* pT{ dynamic_cast<T*>(pC) }) return pT;
			}
			throw std::runtime_error(errorMessage);
		}
		template<class T>
		T* GetpActiveComponent(const std::string& errorMessage) const
		{
			for (Component* pC : m_pComponents)
			{
				if (pC->isActive) if (T* pT{ dynamic_cast<T*>(pC) }) return pT;
			}
			throw std::runtime_error(errorMessage);
		}
	};
}