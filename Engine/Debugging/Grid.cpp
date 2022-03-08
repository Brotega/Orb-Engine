#include "Grid.h"
#include "../Application/Application.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Buffer/VertexBuffer.h"
#include "../Rendering/Buffer/VertexTypes.h"

#include <glad/glad.h>

namespace OrbEngine
{
	Grid::Grid(Application* application) : m_Application(application),
		m_RowCount(11), m_ColCount(11), m_Transform(new Transform()),
		m_VertexBuffer(nullptr)
	{
		/* Add horizontal lines */
		for (int i = 0; i < m_ColCount - 1; i++)
		{
			for (int j = 0; j < m_RowCount; j++)
			{
				float x = static_cast<float>(i - m_ColCount / 2);
				float z = static_cast<float>(j - m_ColCount / 2);
				VertexPosCol vert0;
				vert0.Position = Vector3(x, 0.0f, z);
				vert0.Colour = Color(0.0f, 1.0f, 1.0f, 1.0f);

				x += 1.0f;
				VertexPosCol vert1;
				vert1.Position = Vector3(x, 0.0f, z);
				vert1.Colour = Color(0.0f, 1.0f, 1.0f, 1.0f);

				m_Grid.push_back(vert0);
				m_Grid.push_back(vert1);
			}
		}

		/* Add vertical lines */
		for (int i = 0; i < m_ColCount; i++)
		{
			for (int j = 0; j < m_RowCount - 1; j++)
			{
				float x = static_cast<float>(i - m_ColCount / 2);
				float z = static_cast<float>(j - m_ColCount / 2);
				VertexPosCol vert0;
				vert0.Position = Vector3(x, 0.0f, z);
				vert0.Colour = Color(0.0f, 1.0f, 1.0f, 1.0f);

				z += 1.0f;
				VertexPosCol vert1;
				vert1.Position = Vector3(x, 0.0f, z);
				vert1.Colour = Color(0.0f, 1.0f, 1.0f, 1.0f);

				m_Grid.push_back(vert0);
				m_Grid.push_back(vert1);
			}
		}

		m_VertexBuffer = new VertexBuffer(m_Grid, VertexBuffer::Primitive::LINES);

		m_Shader = m_Application->GetAssetManager()->GetShader("Debug");
		m_Transform->UpdateLocalToWorldMatrix();
	}

	Grid::Grid(Application* application, int rowCount, int colCount) : m_Application(application),
		m_RowCount(rowCount), m_ColCount(colCount), m_Transform(new Transform()),
		m_VertexBuffer(nullptr)
	{
		/* Add horizontal lines */
		for (int i = 0; i < m_ColCount - 1; i++)
		{
			for (int j = 0; j < m_RowCount; j++)
			{
				float x = static_cast<float>(i - m_ColCount / 2);
				float z = static_cast<float>(j - m_ColCount / 2);
				VertexPosCol vert0;
				vert0.Position = Vector3(x, 0.0f, z);
				vert0.Colour = Color(1.0f, 1.0f, 1.0f, 1.0f);

				x += 1.0f;
				VertexPosCol vert1;
				vert1.Position = Vector3(x, 0.0f, z);
				vert1.Colour = Color(1.0f, 1.0f, 1.0f, 1.0f);

				m_Grid.push_back(vert0);
				m_Grid.push_back(vert1);
			}
		}

		/* Add vertical lines */
		for (int i = 0; i < m_ColCount; i++)
		{
			for (int j = 0; j < m_RowCount - 1; j++)
			{
				float x = static_cast<float>(i - m_ColCount / 2);
				float z = static_cast<float>(j - m_ColCount / 2);
				VertexPosCol vert0;
				vert0.Position = Vector3(x, 0.0f, z);
				vert0.Colour = Color(1.0f, 1.0f, 1.0f, 1.0f);

				z += 1.0f;
				VertexPosCol vert1;
				vert1.Position = Vector3(x, 0.0f, z);
				vert1.Colour = Color(1.0f, 1.0f, 1.0f, 1.0f);

				m_Grid.push_back(vert0);
				m_Grid.push_back(vert1);
			}
		}

		m_VertexBuffer = new VertexBuffer(m_Grid, VertexBuffer::Primitive::LINES);

		m_Shader = m_Application->GetAssetManager()->GetShader("Debug");
		m_Transform->UpdateLocalToWorldMatrix();
	}

	Grid::~Grid()
	{
		delete m_Transform;
		delete m_VertexBuffer;
	}

	void Grid::Draw()
	{
		m_Shader->Use();
		Matrix4x4 model = m_Transform->GetLocalToWorldMatrix();
		m_Shader->SetMatrix4x4("model", model);
		m_VertexBuffer->Draw();
	}
}