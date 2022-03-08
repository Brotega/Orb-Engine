#include "VertexBuffer.h"
#include "VertexTypes.h"
#include "../../Rendering/Mesh.h"

#include <glad/glad.h>

namespace OrbEngine
{
	VertexBuffer::VertexBuffer(const std::vector<VertexPosNormTanBitUV>& vertices, const Primitive& primitive) :
		m_NumVertices(static_cast<int>(vertices.size())), m_VAO(0), m_VBO(0), m_PrimitiveFlag(0)
	{
		switch (primitive)
		{
		case Primitive::POINTS:
			m_PrimitiveFlag = GL_POINTS;
			break;
			
		case Primitive::LINES:
			m_PrimitiveFlag = GL_LINES;
			break;

		case Primitive::TRIANGLES:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;

		default:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;
		}

		int strideBytes = sizeof(VertexPosNormTanBitUV);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosNormTanBitUV, Position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosNormTanBitUV, Normal));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosNormTanBitUV, Tangent));
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosNormTanBitUV, Bitangent));
		glEnableVertexAttribArray(3);

		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosNormTanBitUV, UV));
		glEnableVertexAttribArray(4);

		glBindVertexArray(0);
	}

	VertexBuffer::VertexBuffer(const std::vector<VertexPosColUV>& vertices, const Primitive& primitive) :
		m_NumVertices(static_cast<int>(vertices.size())), m_VAO(0), m_VBO(0), m_PrimitiveFlag(0)
	{
		switch (primitive)
		{
		case Primitive::POINTS:
			m_PrimitiveFlag = GL_POINTS;
			break;

		case Primitive::LINES:
			m_PrimitiveFlag = GL_LINES;
			break;

		case Primitive::TRIANGLES:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;

		default:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;
		}

		int strideBytes = sizeof(VertexPosColUV);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosColUV, Position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosColUV, Colour));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosColUV, UV));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	VertexBuffer::VertexBuffer(const std::vector<VertexPosUV>& vertices, const Primitive& primitive) :
		m_NumVertices(static_cast<int>(vertices.size())), m_VAO(0), m_VBO(0), m_PrimitiveFlag(0)
	{
		switch (primitive)
		{
		case Primitive::POINTS:
			m_PrimitiveFlag = GL_POINTS;
			break;

		case Primitive::LINES:
			m_PrimitiveFlag = GL_LINES;
			break;

		case Primitive::TRIANGLES:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;

		default:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;
		}

		int strideBytes = sizeof(VertexPosUV);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosUV, Position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosUV, UV));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	VertexBuffer::VertexBuffer(const std::vector<VertexPosCol>& vertices, const Primitive& primitive) :
		m_NumVertices(static_cast<int>(vertices.size())), m_VAO(0), m_VBO(0), m_PrimitiveFlag(0)
	{
		switch (primitive)
		{
		case Primitive::POINTS:
			m_PrimitiveFlag = GL_POINTS;
			break;

		case Primitive::LINES:
			m_PrimitiveFlag = GL_LINES;
			break;

		case Primitive::TRIANGLES:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;

		default:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;
		}

		int strideBytes = sizeof(VertexPosCol);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosCol, Position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosCol, Colour));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	VertexBuffer::VertexBuffer(const std::vector<VertexPos>& vertices, const Primitive& primitive) :
		m_NumVertices(static_cast<int>(vertices.size())), m_VAO(0), m_VBO(0), m_PrimitiveFlag(0)
	{
		switch (primitive)
		{
		case Primitive::POINTS:
			m_PrimitiveFlag = GL_POINTS;
			break;

		case Primitive::LINES:
			m_PrimitiveFlag = GL_LINES;
			break;

		case Primitive::TRIANGLES:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;

		default:
			m_PrimitiveFlag = GL_TRIANGLES;
			break;
		}

		int strideBytes = sizeof(VertexPos);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPos, Position));
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void VertexBuffer::Draw() const
	{
		glBindVertexArray(m_VAO);
		glDrawArrays(m_PrimitiveFlag, 0, m_NumVertices);
		glBindVertexArray(0);
	}
}