#pragma once
#include "Component.h"
#include "Command.h"

namespace e
{
	enum Flip { o = 0x00000000, x = 0x00000001, y = 0x00000002, xy = 0x00000003 };
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(short x = 0, short y = 0, float scale = 1);
		explicit TransformComponent(const SPoint& position = { 0, 0 }, float scale = 1);
		void ResetScale();
		void Scale(const float& scalar);
		void Scale(const FVector& scalars);
		Command* CreateMoveCommand(const SVector& movement);
		//Variables
		SPoint position;
		FVector scale;
		short rotation;
		Flip flip;
	
		//COMMANDS
		class MoveCommand final : public Command
		{
		public:
			MoveCommand(TransformComponent* pTransformComponent, const SVector& movement) : 
				m_pTransformComponent{ pTransformComponent },
				m_Movement{ movement }
			{}
			void SetMovement(SVector movement) { m_Movement = movement; };
			virtual void Execute() override
			{
				if(m_pTransformComponent->isActive)
				{
					m_pTransformComponent->position += m_Movement;
					int flipX{ 0 < m_Movement.x ? Flip::o : Flip::x };
					if (0 == m_Movement.x) flipX &= m_pTransformComponent->flip; //neutralize flipping
					int flipY{ 0 < m_Movement.y ? Flip::o : Flip::y };
					if (0 == m_Movement.y) flipY &= m_pTransformComponent->flip; //neutralize flipping
					m_pTransformComponent->flip = e::Flip(flipX | flipY);
				}
			}
		private:
			TransformComponent* m_pTransformComponent;
			SVector m_Movement;
		};
	};
}