#pragma once
#include <string>
#include <vector>

namespace OrbEngine
{
	/* Forward declarations */
	class Color;
	class Matrix3x3;
	class Matrix4x4;
	class Graphics;
	class Vector2;
	class Vector3;
	class Vector4;

	enum class ShaderPropertyEnumType
	{
		FLOAT,
		VEC2,
		VEC3,
		VEC4,
		DOUBLE, 
		INT,
		UNSIGNED_INT,
		BOOL,
		MAT3,
		MAT4,
		SAMPLER2D,
		SAMPLER3D,
		SAMPLERCUBE,
		UNDEFINED
	};

	class ShaderProperty
	{
	public:
		/* Constructors/destructor */
		ShaderProperty() : m_IsExposed(true), m_UniformLocation(0), m_ShaderPropertyEnumType(ShaderPropertyEnumType::UNDEFINED) { }

		ShaderProperty(ShaderPropertyEnumType shaderPropertyType, int uniformLocation) :
			m_IsExposed(true), m_UniformLocation(uniformLocation), m_ShaderPropertyEnumType(shaderPropertyType) { }

		ShaderProperty(ShaderPropertyEnumType shaderPropertyType, int uniformLocation, const std::string& name) :
			m_IsExposed(true), m_UniformLocation(uniformLocation), m_ShaderPropertyEnumType(shaderPropertyType), m_Name(name) { }

		ShaderProperty(ShaderPropertyEnumType shaderPropertyType, int uniformLocation, bool isExposed) :
			m_IsExposed(isExposed), m_UniformLocation(uniformLocation), m_ShaderPropertyEnumType(shaderPropertyType) { }

		ShaderProperty(ShaderPropertyEnumType shaderPropertyType, int uniformLocation, const std::string& name, bool isExposed) :
			m_IsExposed(isExposed), m_UniformLocation(uniformLocation), m_ShaderPropertyEnumType(shaderPropertyType), m_Name(name) { }

		~ShaderProperty() { }

		/* Main functions */
		bool IsExposed() const { return m_IsExposed; }

		/* Setters */
		void SetExposed(bool val) { m_IsExposed = val; }
		void SetPropertyType(ShaderPropertyEnumType property) { m_ShaderPropertyEnumType = property; }
		void SetName(const std::string& name) { m_Name = name; }
		void SetUniformLocation(int uniformLocation) { m_UniformLocation = uniformLocation; }

		/* Getters */
		ShaderPropertyEnumType GetPropertyType() const { return m_ShaderPropertyEnumType; }
		int GetUniformLocation() const { return m_UniformLocation; }
		std::string GetName() const { return m_Name; }

	protected:
		ShaderPropertyEnumType m_ShaderPropertyEnumType;
		int m_UniformLocation;
		std::string m_Name;
		bool m_IsExposed;
	};

	class Shader
	{
	public:

		/* Constructors/destructor */
		Shader(const Shader& other);
		Shader();
		~Shader();

		/* Main functions */
		bool Load(const std::string& vertexFilename, const std::string& fragmentFilename);
		void Use();
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetUnsignedInt(const std::string& name, unsigned int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetDouble(const std::string& name, double value) const;
		void SetVector2(const std::string& name, const Vector2& vec2) const;
		void SetVector3(const std::string& name, const Vector3& vec3) const;
		void SetVector4(const std::string& name, const Vector4& vec4) const;
		void SetColor(const std::string& name, const Color& color) const;
		void SetMatrix3x3(const std::string& name, const Matrix3x3& mat3x3) const;
		void SetMatrix4x4(const std::string& name, const Matrix4x4& mat4x4) const;

		/* Getters */
		std::vector<ShaderProperty> GetShaderProperties() const { return m_ShaderProperties; }

	private:
		unsigned int m_ShaderID;
		std::vector<ShaderProperty> m_ShaderProperties;

		/* Internal functions */
		bool CheckCompileErrors(unsigned int shader, const char* type);
		void FillInPropertiesFromGLType(const std::string& name, unsigned int type, int uniformLocation);
	};
}