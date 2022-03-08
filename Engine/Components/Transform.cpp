#include "Transform.h"
#include <iostream>

namespace OrbEngine
{
	//--------Define Transform constants--------
	const Transform Transform::Default;
	//------------------------------------------


	Transform::Transform() :
		m_Forward(Vector3::Forward), m_Left(Vector3::Left), m_Up(Vector3::Up),
		m_Scale(Vector3::One), m_Position(Vector3::Zero), m_Rotation(Quaternion::Identity)
	{

	}

	Transform::Transform(const Transform& transform)
	{
		m_Forward = transform.m_Forward;
		m_Left = transform.m_Left;
		m_Up = transform.m_Up;

		m_Position = transform.m_Position;
		m_Scale = transform.m_Scale;
		m_Rotation = transform.m_Rotation;

		m_LocalToWorldMatrix = transform.m_LocalToWorldMatrix;
	}

	Transform::~Transform()
	{

	}

	void Transform::SetRotation(const Quaternion& rotation)
	{
		m_Rotation = rotation;
		Matrix4x4 rot = m_Rotation.ToMatrix4x4();
		m_Left = rot.GetXAxis();
		m_Up = rot.GetYAxis();
		m_Forward = rot.GetZAxis();
	}

	void Transform::AxisAngle(const Vector3& axis, float angle)
	{
		Vector3 normAxis = Vector3::Normalize(axis);
		m_Rotation = Quaternion(normAxis, angle);
		Matrix4x4 rot = m_Rotation.ToMatrix4x4();
		m_Left = rot.GetXAxis();
		m_Up = rot.GetYAxis();
		m_Forward = rot.GetZAxis();
	}

	void Transform::LookAt(const Vector3& targetPosition, const Vector3& up = Vector3::Up)
	{
		Matrix4x4 lookAt = Matrix4x4::CreateLookAtMatrix(m_Position, targetPosition, up);
		lookAt.Transpose();
		m_Rotation = lookAt.ToQuaternion();
		m_Forward = lookAt.GetZAxis();
		m_Left = lookAt.GetXAxis();
		m_Up = lookAt.GetYAxis();
	}

	void Transform::UpdateLocalToWorldMatrix()
	{
		m_LocalToWorldMatrix = Matrix4x4::CreateScaleMatrix(m_Scale) * m_Rotation.ToMatrix4x4() * Matrix4x4::CreateTranslationMatrix(m_Position);
	}
}