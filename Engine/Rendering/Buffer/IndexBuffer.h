#pragma once

#include <vector>

namespace OrbEngine
{
	/* Forward declarations */
	struct VertexPosNormTanBitUV;
	struct VertexPosColUV;
	struct VertexPosUV;
	struct VertexPosCol;
	struct VertexPos;

	class IndexBuffer
	{
	public:
		/* Constructors/destructor */
		IndexBuffer(const std::vector<VertexPosNormTanBitUV>& vertices, const std::vector<unsigned int>& indices);
		IndexBuffer(const std::vector<VertexPosColUV>& vertices, const std::vector<unsigned int>& indices);
		IndexBuffer(const std::vector<VertexPosUV>& vertices, const std::vector<unsigned int>& indices);
		IndexBuffer(const std::vector<VertexPosCol>& vertices, const std::vector<unsigned int>& indices);
		IndexBuffer(const std::vector<VertexPos>& vertices, const std::vector<unsigned int>& indices);
		~IndexBuffer();

		/* Main functions */
		void Draw() const;

	private:
		int m_NumVertices;
		int m_NumIndices;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
	};
}