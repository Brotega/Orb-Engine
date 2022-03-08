#include "FreeMoveCamera.h"
#include "../../Application/Application.h"
#include "../../Components/Camera.h"
#include "../../Components/Transform.h"
#include "../../Debugging/CoordinateSystem.h"
#include "../../Input/InputSystem.h"
#include "../../Rendering/Mesh.h"
#include "../../Rendering/Shader.h"

#include <SDL2/SDL.h>

namespace OrbEngine
{
	FreeMoveCamera::FreeMoveCamera(Application* application) :
		Actor(application), m_MoveSpeed(5.0f), m_MoveState(0), m_Pitch(0.0f), m_Yaw(0.0f)
	{

	}

	FreeMoveCamera::FreeMoveCamera(Application* application, const std::string& actorName) :
		Actor(application, actorName), m_MoveSpeed(5.0f), m_MoveState(0), m_Pitch(0.0f), m_Yaw(0.0f)
	{

	}

	FreeMoveCamera::~FreeMoveCamera()
	{

	}

	void FreeMoveCamera::Update(float deltaTime)
	{
		Vector3 direction = Vector3::Zero;

		if (m_MoveState & (MoveState::FORWARD)) direction += Vector3::Forward;
		if (m_MoveState & (MoveState::LEFT)) direction += Vector3::Left;
		if (m_MoveState & (MoveState::RIGHT)) direction += Vector3::Right;
		if (m_MoveState & (MoveState::BACKWARD)) direction += Vector3::Backward;
		if (m_MoveState & (MoveState::UP)) direction += Vector3::Up;
		if (m_MoveState & (MoveState::DOWN)) direction += Vector3::Down;

		direction = m_Transform->GetForward() * direction.z +
			m_Transform->GetLeft() * direction.x +
			m_Transform->GetUp() * direction.y;
		
		m_Transform->SetPosition(m_Transform->GetPosition() + direction * m_MoveSpeed * deltaTime);

		m_Transform->UpdateLocalToWorldMatrix();
	}

	void FreeMoveCamera::RotateLookDirection(const Vector2& deltaMouse)
	{
		m_Yaw -= deltaMouse.x * 0.05f;
		m_Pitch -= deltaMouse.y * 0.05f;

		if (m_Pitch > 89.0f) m_Pitch = 89.0f;
		if (m_Pitch < -89.0f) m_Pitch = -89.0f;

		Vector3 lookDirection = m_Transform->GetForward();
		lookDirection.x = Math::Sin(m_Yaw * Math::Deg2Rad) * Math::Cos(m_Pitch * Math::Deg2Rad);
		lookDirection.y = Math::Sin(m_Pitch * Math::Deg2Rad);
		lookDirection.z = Math::Cos(m_Yaw * Math::Deg2Rad) * Math::Cos(m_Pitch * Math::Deg2Rad);
		lookDirection.Normalize();

		m_Transform->LookAt(m_Transform->GetPosition() + lookDirection, Vector3::Up);
		m_Transform->UpdateLocalToWorldMatrix();
	}
}