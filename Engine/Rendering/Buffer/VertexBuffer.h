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

	class VertexBuffer
	{
	public:
		enum class Primitive
		{
			POINTS,
			LINES,
			TRIANGLES
		};

		/* Constructors/destructor */
		VertexBuffer(const std::vector<VertexPosNormTanBitUV>& vertices, const Primitive& primitives = Primitive::TRIANGLES);
		VertexBuffer(const std::vector<VertexPosColUV>& vertices, const Primitive& primitives = Primitive::TRIANGLES);
		VertexBuffer(const std::vector<VertexPosUV>& vertices, const Primitive& primitives = Primitive::TRIANGLES);
		VertexBuffer(const std::vector<VertexPosCol>& vertices, const Primitive& primitives = Primitive::TRIANGLES);
		VertexBuffer(const std::vector<VertexPos>& vertices, const Primitive& primitives = Primitive::TRIANGLES);
		~VertexBuffer();

		/* Main functions */
		void Draw() const;

	private:
		int m_NumVertices;
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_PrimitiveFlag;
	};
}