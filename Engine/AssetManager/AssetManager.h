#pragma once

#include "../Rendering/Cubemap.h"
#include "../Rendering/Material.h"
#include "../Rendering/Mesh.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Texture2D.h"

#include <string>
#include <unordered_map>

namespace OrbEngine
{
	/* Forward declarations */
	class Application;

	template<typename T>
	class AssetCache
	{
	public:
		/* Constructors/destructor */
		AssetCache() {};
		~AssetCache()
		{
			for (auto asset : m_Map)
			{
				delete asset.second;
			}
			m_Map.clear();
		}

		T* Load(const std::string& filename);
		void Store(const std::string& filename, T* asset);
		void Delete(const std::string& filename);

	private:
		std::unordered_map<std::string, T*> m_Map;
	};

	class AssetManager
	{
	public:
		/* Constructors/destructor */
		AssetManager();
		~AssetManager();

		/* Main functions */
		void StoreMesh(const std::string& name, Mesh* mesh);
		void StoreTexture(const std::string& name, Texture2D* texture);
		void StoreShader(const std::string& name, Shader* shader);
		void StoreMaterial(const std::string& name, Material* material);
		void StoreCubeMap(const std::string& name, CubeMap* cubeMap);
		Mesh* GetModel(const std::string& name);
		Texture2D* GetTexture(const std::string& name);
		Shader* GetShader(const std::string& name);
		Material* GetMaterial(const std::string& name);
		CubeMap* GetCubeMap(const std::string& name);

		/* Getters */
		std::string GetAssetRootDirectory() const { return m_AssetRootDirectory; }
		std::string GetModelRootDirectory() const { return m_ModelRootDirectory; }
		std::string GetTextureRootDirectory() const { return m_TextureRootDirectory; }
		std::string GetShaderRootDirectory() const { return m_ShaderRootDirectory; }
		std::string GetCubeMapRootDirectory() const { return m_CubeMapRootDirectory; }

	private:
		std::string m_AssetRootDirectory = "Assets/";
		std::string m_ModelRootDirectory = "Assets/Models/";
		std::string m_TextureRootDirectory = "Assets/Textures/";
		std::string m_ShaderRootDirectory = "Assets/Shaders/";
		std::string m_CubeMapRootDirectory = "Assets/CubeMaps/";

		AssetCache<Shader> m_ShaderCache;
		AssetCache<Texture2D> m_TextureCache;
		AssetCache<Mesh> m_MeshCache;
		AssetCache<Material> m_MaterialCache;
		AssetCache<CubeMap> m_CubeMapCache;
	};

	template<typename T>
	inline T* AssetCache<T>::Load(const std::string& name)
	{
		auto iter = m_Map.find(name);

		if (iter != m_Map.end())
		{
			return iter->second;
		}

		return nullptr;
	}

	template<typename T>
	inline void AssetCache<T>::Store(const std::string& name, T* asset)
	{
		m_Map[name] = asset;
	}

	template<typename T>
	inline void AssetCache<T>::Delete(const std::string& name)
	{
		auto iter = m_Map.find(name);

		if (iter != m_Map.end())
		{
			delete iter->second;
			m_Map.erase(iter);
		}

		return;
	}
}
