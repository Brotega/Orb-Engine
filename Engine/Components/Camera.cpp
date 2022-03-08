#include "Camera.h"
#include "../Actors/Actor.h"
#include "../Components/MeshRenderer.h"
#include "../Math/Math.h"
#include "../Rendering/Buffer/UniformBuffer.h"
#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"

#include <glad/glad.h>

namespace OrbEngine
{
	Camera::Camera() :
		Component(),
		m_FOV(0.0f), m_ZNear(0.0f), m_ZFar(0.0f), m_Width(0.0f), m_Height(0.0f),
		m_CameraProjectionType(ProjectionType::UNDEFINED), 
		m_BackgroundType(BackgroundType::SOLID_COLOR),
		m_BackgroundColor(Color::Black)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::SetAllCameraParameters(float zNear, float zFar, float width, float height)
	{
		m_CameraProjectionType = ProjectionType::ORTHOGRAPHIC;
		m_ZNear = zNear;
		m_ZFar = zFar;
		m_Width = width;
		m_Height = height;
	}

	void Camera::SetAllCameraParameters(float zNear, float zFar, float width, float height, float fov)
	{
		m_CameraProjectionType = ProjectionType::PERSPECTIVE;
		m_ZNear = zNear;
		m_ZFar = zFar;
		m_Width = width;
		m_Height = height;
		m_FOV = fov;
	}

	Matrix4x4 Camera::GetViewMatrix() const
	{
		Vector3 position = m_Actor->GetTransform()->GetPosition();
		Vector3 forward = m_Actor->GetTransform()->GetForward();

		return Matrix4x4::CreateLookAtMatrix(position, position - forward, Vector3::Up);
	}

	Matrix4x4 Camera::GetProjectionMatrix() const
	{
		switch (m_CameraProjectionType)
		{
		case ProjectionType::ORTHOGRAPHIC:
			return Matrix4x4::CreateOrthographicMatrix(m_Width, m_Height, m_ZNear, m_ZFar);
			break;

		case ProjectionType::PERSPECTIVE:
			return Matrix4x4::CreatePerspectiveMatrix(m_Width, m_Height, m_ZNear, m_ZFar, Math::Deg2Rad * m_FOV);
			break;
		}

		return Matrix4x4::CreatePerspectiveMatrix(m_Width, m_Height, m_ZNear, m_ZFar, Math::Deg2Rad * m_FOV);
	}

	Matrix4x4 Camera::GetOrthogonalMatrix() const
	{
		return Matrix4x4::CreateOrthographicMatrix(m_Width, m_Height, m_ZNear, m_ZFar);
	}

	Matrix4x4 Camera::GetPerspectiveMatrix() const
	{
		return Matrix4x4::CreatePerspectiveMatrix(m_Width, m_Height, m_ZNear, m_ZFar, Math::Deg2Rad * m_FOV);
	}
}