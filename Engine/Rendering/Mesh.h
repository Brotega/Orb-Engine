#pragma once

#include "../Math/Math.h"
#include "../Rendering/Color.h"

#include <vector>
#include <string>

/* Assimp structs */
struct aiNode;
struct aiMaterial;
struct aiMesh;
struct aiScene;

namespace OrbEngine
{
	/* Forward declarations */
	class IndexBuffer;
	class Shader;
	struct VertexPosNormTanBitUV;
	class Texture2D;

	class Mesh
	{
	public:
		/* Constructors/destructor */
		Mesh();
		~Mesh();

		/* Main functions */
		void Draw() const;
		bool Load(const std::string& filenamePath);

	private:
		IndexBuffer* m_IndexBuffer;

		std::vector<VertexPosNormTanBitUV> m_Vertices;
		std::vector<unsigned int> m_Indices;

		void ProcessAINode(aiNode* node, const aiScene* scene);
		void ProcessAIMesh(aiMesh* mesh, const aiScene* scene);
	};
}