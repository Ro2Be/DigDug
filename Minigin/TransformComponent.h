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
		explicit TransformComponent(const SPoint& position, float scale = 1);
		SPoint GetWorldPosition() const;
		FVector GetWorldScale() const;
		short GetWorldRotation() const;
		Flip GetWorldFlip() const;
		void ResetScale();
		void Scale(const float& scalar);
		void Scale(const FVector& scalars);
		Command* CreateMoveCommand(const SVector& movement);
		//Variables
		TransformComponent* pParent;
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
					m_pTransformComponent->rotation = (m_Movement.y == 0 ? 0 : 90);
					m_pTransformComponent->flip = ((m_Movement.x < 0 || m_Movement.y < 0) ? Flip::x : Flip::o);

					//FLIPPING TO COMBINE WITH SECOND ROTATED ANIMATION
					//m_pTransformComponent->position += m_Movement;
					//int flipX{ 0 < m_Movement.x ? Flip::o : Flip::x };
					//if (m_Movement.x == 0) flipX &= m_pTransformComponent->flip; //neutralize flipping
					//int flipY{ 0 < m_Movement.y ? Flip::o : Flip::y };
					//if (m_Movement.y == 0) flipY &= m_pTransformComponent->flip; //neutralize flipping
					//m_pTransformComponent->flip = e::Flip(flipX | flipY);
				}
			}
		private:
			TransformComponent* m_pTransformComponent;
			SVector m_Movement;
		};
	};
}