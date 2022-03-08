#include "IndexBuffer.h"
#include "VertexTypes.h"
#include "../Mesh.h"

#include <glad/glad.h>

namespace OrbEngine
{
	IndexBuffer::IndexBuffer(const std::vector<VertexPosNormTanBitUV>& vertices, const std::vector<unsigned int>& indices) :
		m_NumVertices(static_cast<int>(vertices.size())), m_NumIndices(static_cast<int>(indices.size()))
	{
		int strideBytes = sizeof(VertexPosNormTanBitUV);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndices, &indices[0], GL_STATIC_DRAW);

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

	IndexBuffer::IndexBuffer(const std::vector<VertexPosColUV>& vertices, const std::vector<unsigned int>& indices) :
		m_NumVertices(static_cast<int>(vertices.size())), m_NumIndices(static_cast<int>(indices.size()))
	{
		int strideBytes = sizeof(VertexPosColUV);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndices, &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosColUV, Position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosColUV, Colour));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosColUV, UV));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	IndexBuffer::IndexBuffer(const std::vector<VertexPosUV>& vertices, const std::vector<unsigned int>& indices) :
		m_NumVertices(static_cast<int>(vertices.size())), m_NumIndices(static_cast<int>(indices.size()))
	{
		int strideBytes = sizeof(VertexPosUV);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndices, &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosUV, Position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosUV, UV));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	IndexBuffer::IndexBuffer(const std::vector<VertexPosCol>& vertices, const std::vector<unsigned int>& indices) :
		m_NumVertices(static_cast<int>(vertices.size())), m_NumIndices(static_cast<int>(indices.size()))
	{
		int strideBytes = sizeof(VertexPosCol);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndices, &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosCol, Position));
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPosCol, Colour));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	IndexBuffer::IndexBuffer(const std::vector<VertexPos>& vertices, const std::vector<unsigned int>& indices) :
		m_NumVertices(static_cast<int>(vertices.size())), m_NumIndices(static_cast<int>(indices.size()))
	{
		int strideBytes = sizeof(VertexPos);
		int sizeBytes = strideBytes * static_cast<unsigned int>(vertices.size());

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeBytes, &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_NumIndices, &indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, strideBytes, (void*)offsetof(VertexPos, Position));
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void IndexBuffer::Draw() const
	{
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_NumIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}