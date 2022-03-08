#include "CoordinateSystem.h"
#include "../Application/Application.h"
#include "../Actors/Actor.h"
#include "../Components/Camera.h"
#include "../Components/Transform.h"
#include "../AssetManager/AssetManager.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Color.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Buffer/VertexBuffer.h"
#include "../Rendering/Buffer/VertexTypes.h"

#include <glad/glad.h>

namespace OrbEngine
{
	CoordinateSystem::CoordinateSystem() :
		m_Transform(new Transform()),
		m_VertexBuffer(nullptr), m_Shader(nullptr)
	{
		Vector3 position = m_Transform->GetPosition();
		Vector3 forward = m_Transform->GetForward();
		Vector3 left = m_Transform->GetLeft();
		Vector3 up = m_Transform->GetUp();

		std::vector<VertexPosCol> defaultCoordinateAxis =
		{
			{Vector3(position),           Color(1.0f, 0.0f, 0.0f)},
			{Vector3(position + forward), Color(1.0f, 0.0f, 0.0f)},
			{Vector3(position),           Color(0.0f, 0.0f, 1.0f)},
			{Vector3(position + left),    Color(0.0f, 0.0f, 1.0f)},
			{Vector3(position),           Color(0.0f, 1.0f, 0.0f)},
			{Vector3(position + up),      Color(0.0f, 1.0f, 0.0f)}
		};

		m_VertexBuffer = new VertexBuffer(defaultCoordinateAxis, VertexBuffer::Primitive::LINES);
	}

	CoordinateSystem::~CoordinateSystem()
	{
		delete m_Transform;
		delete m_VertexBuffer;
	}

	void CoordinateSystem::Draw() const
	{
		m_Shader->Use();
		Matrix4x4 translate = Matrix4x4::CreateTranslationMatrix(m_Transform->GetPosition());
		Matrix4x4 rotate = m_Transform->GetRotationMatrix4x4();
		Matrix4x4 model = rotate * translate;
		m_Shader->SetMatrix4x4("model", model);
		m_VertexBuffer->Draw();
	}

	void CoordinateSystem::SetPosition(const Vector3& position) { m_Transform->SetPosition(position); }
	void CoordinateSystem::SetRotation(const Quaternion& rotation) { m_Transform->SetRotation(rotation); }
	void CoordinateSystem::SetScale(const Vector3& scale) { m_Transform->SetScale(scale); }

	void CoordinateSystem::UpdateAxis()
	{
		Matrix4x4 translate = Matrix4x4::CreateTranslationMatrix(m_Transform->GetPosition());
		Matrix4x4 scale = Matrix4x4::CreateScaleMatrix(m_Transform->GetScale());
		Matrix4x4 rotate = m_Transform->GetRotationMatrix4x4();
		m_Transform->SetLocalToWorldMatrix(scale * rotate * translate);
	}
}