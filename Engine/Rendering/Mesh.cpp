#include "Mesh.h"
#include "../Actors/Actor.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Texture2D.h"
#include "../Rendering/Buffer/IndexBuffer.h"
#include "../Rendering/Buffer/VertexTypes.h"

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

namespace OrbEngine
{
	Mesh::Mesh() :
		m_IndexBuffer(nullptr)
	{

	}


	Mesh::~Mesh()
	{
		delete m_IndexBuffer;
	}

	void Mesh::Draw() const
	{
		m_IndexBuffer->Draw();
	}

	bool Mesh::Load(const std::string& filenamePath)
	{
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(filenamePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
			return false;
		}

		ProcessAINode(scene->mRootNode, scene);

		m_IndexBuffer = new IndexBuffer(m_Vertices, m_Indices);

		return true;
	}

	void Mesh::ProcessAINode(aiNode* node, const aiScene* scene)
	{
		// process all the node's meshes (if any)
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			ProcessAIMesh(mesh, scene);
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessAINode(node->mChildren[i], scene);
		}
	}

	void Mesh::ProcessAIMesh(aiMesh* mesh, const aiScene* scene)
	{

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			VertexPosNormTanBitUV vertex;
			float posX = mesh->mVertices[i].x;
			float posY = mesh->mVertices[i].y;
			float posZ = mesh->mVertices[i].z;
			vertex.Position = Vector3(posX, posY, posZ);

			if (mesh->HasNormals())
			{
				float normX = mesh->mNormals[i].x;
				float normY = mesh->mNormals[i].y;
				float normZ = mesh->mNormals[i].z;
				vertex.Normal = Vector3(normX, normY, normZ);

				float tangentX = mesh->mTangents[i].x;
				float tangentY = mesh->mTangents[i].y;
				float tangentZ = mesh->mTangents[i].z;
				vertex.Tangent = Vector3(tangentX, tangentY, tangentZ);

				float bitangentX = mesh->mBitangents[i].x;
				float bitangentY = mesh->mBitangents[i].y;
				float bitangentZ = mesh->mBitangents[i].z;
				vertex.Bitangent = Vector3(bitangentX, bitangentY, bitangentZ);
			}

			if (mesh->mTextureCoords[0])
			{
				float texU = mesh->mTextureCoords[0][i].x;
				float texV = mesh->mTextureCoords[0][i].y;
				vertex.UV = Vector2(texU, texV);
			}
			else
				vertex.UV = Vector2::Zero;

			m_Vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				m_Indices.push_back(face.mIndices[j]);
		}
	}
}