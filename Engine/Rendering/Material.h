#pragma once
#include <string>
#include <vector>

namespace OrbEngine
{
	/* Forward declarations */
	class Color;
	class CubeMap;
	class Mesh;
	class Shader;
	class Texture2D;
	class Texture3D;
	class Matrix3x3;
	class Matrix4x4;
	class RenderTexture;
	class Graphics;
	class Vector2;
	class Vector3;
	class Vector4;

	template <typename T>
	struct MaterialProperty
	{
		MaterialProperty(const std::string& name, const T& property) :
			Name(name), Property(property) {}

		std::string Name;
		T Property;
	};

	class Material
	{
	public:
		/* Constructors/destructor */
		Material();
		~Material();

		/* Main functions */
		void SetProperties() const;
		void UseShader() const;
		void SetBool(const std::string& name, bool value);
		void SetInt(const std::string& name, int value);
		void SetFloat(const std::string& name, float value);
		void SetVector2(const std::string& name, const Vector2& vec2);
		void SetVector3(const std::string& name, const Vector3& vec3);
		void SetVector4(const std::string& name, const Vector4& vec4);
		void SetColor(const std::string& name, const Color& color);
		void SetMatrix3x3(const std::string& name, const Matrix3x3& mat3x3);
		void SetMatrix4x4(const std::string& name, const Matrix4x4& mat4x4);
		void SetTexture2D(const std::string& name, Texture2D* texture2D);
		void SetRenderTexture(const std::string& name, RenderTexture* renderTexture);
		void SetCubeMap(const std::string& name, CubeMap* cubeMap);
		void SetShader(Shader* shader);

		/* Setters */
		void SetRenderQueue(int renderQueue) { m_RenderQueue = renderQueue; }

		/* Getters */
		int GetRenderQueue() const { return m_RenderQueue; }
		Shader* GetShader() const { return m_Shader; }

	private:
		Shader* m_Shader;
		int m_RenderQueue;

		// There's probably something better than this but I'll stick with this for now and come back to it 
		// when I start refactoring and improving memory/speed
		std::vector<MaterialProperty<CubeMap*>> m_CubeMapProperties;
		std::vector<MaterialProperty<Texture2D*>> m_Texture2DProperties;
		std::vector<MaterialProperty<Matrix3x3>> m_Matrix3x3Properties;
		std::vector<MaterialProperty<Matrix4x4>> m_Matrix4x4Properties;
		std::vector<MaterialProperty<Color>> m_ColorProperties;
		std::vector<MaterialProperty<Vector4>> m_Vector4Properties;
		std::vector<MaterialProperty<Vector3>> m_Vector3Properties;
		std::vector<MaterialProperty<Vector2>> m_Vector2Properties;
		std::vector<MaterialProperty<float>> m_FloatProperties;
		std::vector<MaterialProperty<bool>> m_BoolProperties;
		std::vector<MaterialProperty<int>> m_IntProperties;
		std::vector<MaterialProperty<unsigned int>> m_UnsignedIntProperties;
		std::vector<MaterialProperty<double>> m_DoubleProperties;
	};
}