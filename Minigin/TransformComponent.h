#pragma once
#include "Component.h"
#include "Command.h"

namespace e
{
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(short x = 0, short y = 0, float scale = 1);
		explicit TransformComponent(const SPoint& position = { 0, 0 }, float scale = 1);
		void SetPosition(short x, short y);
		void SetPosition(const SPoint& position);
		void AddMovement(short x, short y);
		void AddMovement(const SVector& movement);
		void ResetScale();
		void SetScale(const FVector& scale);
		void Scale(const float& scale);
		void Scale(const FVector& scale);
		const SPoint&  GetPosition() const;
		const FVector& GetScale() const;
		Command* CreateMoveCommand(const SVector& movement);
	private:
		SPoint m_Position;
		float m_Depth;
		FVector m_Scale;
		float m_Rotation;
	
		//COMMANDS
		class CommandMove: public Command
		{
		public:
			CommandMove(TransformComponent* pTransformComponent, const SVector& movement) : 
				m_pTransformComponent{ pTransformComponent },
				m_Movement{ movement }
			{}
			void SetMovement(SVector movement) { m_Movement = movement; };
			virtual void Execute() override
			{
				m_pTransformComponent->AddMovement(m_Movement);
			}
		private:
			TransformComponent* m_pTransformComponent;
			SVector m_Movement;
		};
	};
}