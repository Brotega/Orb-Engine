#include "Skybox.h"
#include "Material.h"
#include "Shader.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/VertexTypes.h"

namespace OrbEngine
{
	Skybox::Skybox() :
		m_VertexBuffer(nullptr), m_Material(nullptr)
	{
		std::vector<VertexPos> vertices
		{
            {Vector3(-1.0f,  1.0f, -1.0f)},
			{Vector3(-1.0f, -1.0f, -1.0f)},
			{Vector3( 1.0f, -1.0f, -1.0f)},
			{Vector3( 1.0f, -1.0f, -1.0f)},
			{Vector3( 1.0f,  1.0f, -1.0f)},
			{Vector3(-1.0f,  1.0f, -1.0f)},

			{Vector3(-1.0f, -1.0f,  1.0f)},
			{Vector3(-1.0f, -1.0f, -1.0f)},
			{Vector3(-1.0f,  1.0f, -1.0f)},
			{Vector3(-1.0f,  1.0f, -1.0f)},
			{Vector3(-1.0f,  1.0f,  1.0f)},
			{Vector3(-1.0f, -1.0f,  1.0f)},

			{Vector3( 1.0f, -1.0f, -1.0f)},
			{Vector3( 1.0f, -1.0f,  1.0f)},
			{Vector3( 1.0f,  1.0f,  1.0f)},
			{Vector3( 1.0f,  1.0f,  1.0f)},
			{Vector3( 1.0f,  1.0f, -1.0f)},
			{Vector3( 1.0f, -1.0f, -1.0f)},

			{Vector3(-1.0f, -1.0f,  1.0f)},
			{Vector3(-1.0f,  1.0f,  1.0f)},
			{Vector3( 1.0f,  1.0f,  1.0f)},
			{Vector3( 1.0f,  1.0f,  1.0f)},
			{Vector3( 1.0f, -1.0f,  1.0f)},
			{Vector3(-1.0f, -1.0f,  1.0f)},

			{Vector3(-1.0f,  1.0f, -1.0f)},
			{Vector3( 1.0f,  1.0f, -1.0f)},
			{Vector3( 1.0f,  1.0f,  1.0f)},
			{Vector3( 1.0f,  1.0f,  1.0f)},
			{Vector3(-1.0f,  1.0f,  1.0f)},
			{Vector3(-1.0f,  1.0f, -1.0f)},

			{Vector3(-1.0f, -1.0f, -1.0f)},
			{Vector3(-1.0f, -1.0f,  1.0f)},
			{Vector3( 1.0f, -1.0f, -1.0f)},
			{Vector3( 1.0f, -1.0f, -1.0f)},
			{Vector3(-1.0f, -1.0f,  1.0f)},
			{Vector3( 1.0f, -1.0f,  1.0f)}
		};

		m_VertexBuffer = new VertexBuffer(vertices);
	}

	Skybox::~Skybox()
	{
		delete m_VertexBuffer;
	}

	void Skybox::Draw() const
	{
		if (!m_Material) return;

		m_Material->GetShader()->Use();
		m_Material->SetProperties();
		m_VertexBuffer->Draw();
	}
}