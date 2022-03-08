#pragma once
#include "../Actor.h"
#include "../../Math/Math.h"

namespace OrbEngine
{
	/* Forward declarations */

	class FreeMoveCamera : public Actor
	{
	public:
		/* Constructors/destructor */
		FreeMoveCamera(Application* application);
		FreeMoveCamera(Application* application, const std::string& actorName);
		~FreeMoveCamera();

		/* Main functions */
		void MoveForward() { m_MoveState |= MoveState::FORWARD; }
		void StopForward() { m_MoveState &= ~MoveState::FORWARD; }
		void MoveBackward() { m_MoveState |= MoveState::BACKWARD; }
		void StopBackward() { m_MoveState &= ~MoveState::BACKWARD; }
		void MoveLeft() { m_MoveState |= MoveState::LEFT; }
		void StopLeft() { m_MoveState &= ~MoveState::LEFT; }
		void MoveRight() { m_MoveState |= MoveState::RIGHT; }
		void StopRight() { m_MoveState &= ~MoveState::RIGHT; }
		void MoveUp() { m_MoveState |= MoveState::UP; }
		void StopUp() { m_MoveState &= ~MoveState::UP; }
		void MoveDown() { m_MoveState |= MoveState::DOWN; }
		void StopDown() { m_MoveState &= ~MoveState::DOWN; }
		void SpeedUp() { m_MoveSpeed = 10.0f; }
		void ResetSpeed() { m_MoveSpeed = 5.0f; }
		void RotateLookDirection(const Vector2& deltaMouse);

		/* Override functions */
		void Update(float deltaTime) override;

	private:
		float m_MoveSpeed;
		float m_Yaw;
		float m_Pitch;

		enum MoveState
		{
			FORWARD = 1 << 0,
			BACKWARD = 1 << 1,
			LEFT = 1 << 2,
			RIGHT = 1 << 3,
			UP = 1 << 4,
			DOWN = 1 << 5,
		}; int m_MoveState;
	};
}