#include "AssetManager.h"
#include "../Application/Application.h"

namespace OrbEngine
{
	AssetManager::AssetManager()
	{

	}

	AssetManager::~AssetManager()
	{

	}

	void AssetManager::StoreMesh(const std::string& name, Mesh* mesh)
	{
		m_MeshCache.Store(name, mesh);
	}

	void AssetManager::StoreTexture(const std::string& name, Texture2D* texture)
	{
		m_TextureCache.Store(name, texture);
	}

	void AssetManager::StoreShader(const std::string& name, Shader* shader)
	{
		m_ShaderCache.Store(name, shader);
	}

	void AssetManager::StoreMaterial(const std::string& name, Material* material)
	{
		m_MaterialCache.Store(name, material);
	}

	void AssetManager::StoreCubeMap(const std::string& name, CubeMap* cubeMap)
	{
		m_CubeMapCache.Store(name, cubeMap);
	}

	Mesh* AssetManager::GetModel(const std::string& name)
	{
		return m_MeshCache.Load(name);
	}

	Texture2D* AssetManager::GetTexture(const std::string& name)
	{
		return m_TextureCache.Load(name);
	}

	Shader* AssetManager::GetShader(const std::string& name)
	{
		return m_ShaderCache.Load(name);
	}

	Material* AssetManager::GetMaterial(const std::string& name)
	{
		return m_MaterialCache.Load(name);
	}

	CubeMap* AssetManager::GetCubeMap(const std::string& name)
	{
		return m_CubeMapCache.Load(name);
	}
}