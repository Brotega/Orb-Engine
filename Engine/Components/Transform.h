#pragma once
#include "Component.h"
#include "../Math/Math.h"

namespace OrbEngine
{
	class Transform
	{
	public:
		/* Constructors/destructor */
		Transform();
		Transform(const Transform& transform);
		~Transform();

		/* Main functions */
		void AxisAngle(const Vector3& axis, float angle);
		void LookAt(const Vector3& targetPosition, const Vector3& up);
		void UpdateLocalToWorldMatrix();

		/* Setters */
		void SetActor(Actor* actor) { m_Actor = actor; }
		void SetPosition(const Vector3& position) { m_Position = position; }
		void SetScale(const Vector3& scale) { m_Scale = scale; }
		void SetRotation(const Quaternion& rotation);
		void SetLocalToWorldMatrix(const Matrix4x4& localToWorldMatrix) { m_LocalToWorldMatrix = localToWorldMatrix; }

		/* Getters */
		Vector3 GetForward() const { return m_Forward; }
		Vector3 GetLeft() const { return m_Left; }
		Vector3 GetUp() const { return m_Up; }
		Vector3 GetPosition() const { return m_Position; }
		Vector3 GetScale() const { return m_Scale; }
		Matrix4x4 GetRotationMatrix4x4() const { return m_Rotation.ToMatrix4x4(); }
		Quaternion GetRotationQuaternion() const { return m_Rotation; }
		Matrix4x4 GetLocalToWorldMatrix() const { return m_LocalToWorldMatrix; }

		// Constants
		static const Transform Default;

	private:
		Actor* m_Actor; 

		Vector3 m_Forward;
		Vector3 m_Left;
		Vector3 m_Up;

		Vector3 m_Position;
		Vector3 m_Scale;
		Quaternion m_Rotation;

		Matrix4x4 m_LocalToWorldMatrix;
	};
}