#pragma once
#include "../Math/Math.h"

namespace OrbEngine
{
	/* Forward declarations */
	class Actor;
	class Shader;
	class Transform;
	class VertexBuffer;

	class CoordinateSystem
	{
	public:
		/* Constructors/destructor */
		CoordinateSystem();
		~CoordinateSystem();

		/* Main functions */
		void Draw() const;
		void UpdateAxis();

		/* Setters */
		void SetPosition(const Vector3& position);
		void SetRotation(const Quaternion& rotation);
		void SetScale(const Vector3& scale);
		void SetShader(Shader* shader) { m_Shader = shader; }

	private:
		Transform* m_Transform;
		VertexBuffer* m_VertexBuffer;
		Shader* m_Shader;
	};
}