#include "Material.h"

#include "CubeMap.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture2D.h"
#include "RenderTexture.h"
#include "../Math/Math.h"

namespace OrbEngine
{
	Material::Material() : 
		m_Shader(nullptr), m_RenderQueue(2000)
	{

	}

	Material::~Material()
	{

	}

	void Material::UseShader() const
	{
		m_Shader->Use();
	}

	void Material::SetProperties() const
	{
		for (size_t i = 0; i < m_CubeMapProperties.size(); ++i)
		{
			m_Shader->SetInt(m_CubeMapProperties[i].Name, static_cast<int>(i));
			m_CubeMapProperties[i].Property->SetActiveTexture(static_cast<unsigned int>(i));
			m_CubeMapProperties[i].Property->Bind();
		}

		for (size_t i = 0; i < m_Texture2DProperties.size(); ++i)
		{
			m_Shader->SetInt(m_Texture2DProperties[i].Name, static_cast<int>(i));
			m_Texture2DProperties[i].Property->SetActiveTexture(static_cast<unsigned int>(i));
			m_Texture2DProperties[i].Property->Bind();
		}

		for (size_t i = 0; i < m_ColorProperties.size(); ++i)
		{
			m_Shader->SetColor(m_ColorProperties[i].Name, m_ColorProperties[i].Property);
		}

		for (size_t i = 0; i < m_Matrix3x3Properties.size(); ++i)
		{
			m_Shader->SetMatrix3x3(m_Matrix3x3Properties[i].Name, m_Matrix3x3Properties[i].Property);
		
		}

		for (size_t i = 0; i < m_Matrix4x4Properties.size(); ++i)
		{
			m_Shader->SetMatrix4x4(m_Matrix4x4Properties[i].Name, m_Matrix4x4Properties[i].Property);
		}

		for (size_t i = 0; i < m_Vector4Properties.size(); ++i)
		{
			m_Shader->SetVector4(m_Vector4Properties[i].Name, m_Vector4Properties[i].Property);
		}

		for (size_t i = 0; i < m_Vector3Properties.size(); ++i)
		{
			m_Shader->SetVector3(m_Vector3Properties[i].Name, m_Vector3Properties[i].Property);
		}

		for (size_t i = 0; i < m_Vector2Properties.size(); ++i)
		{
			m_Shader->SetVector2(m_Vector2Properties[i].Name, m_Vector2Properties[i].Property);
		}

		for (size_t i = 0; i < m_FloatProperties.size(); ++i)
		{
			m_Shader->SetFloat(m_FloatProperties[i].Name, m_FloatProperties[i].Property);
		}

		for (size_t i = 0; i < m_BoolProperties.size(); ++i)
		{
			m_Shader->SetBool(m_BoolProperties[i].Name, m_BoolProperties[i].Property);
		}

		for (size_t i = 0; i < m_IntProperties.size(); ++i)
		{
			m_Shader->SetInt(m_IntProperties[i].Name, m_BoolProperties[i].Property);
		}

		for (size_t i = 0; i < m_UnsignedIntProperties.size(); ++i)
		{
			m_Shader->SetUnsignedInt(m_UnsignedIntProperties[i].Name, m_UnsignedIntProperties[i].Property);
		}

		for (size_t i = 0; i < m_DoubleProperties.size(); ++i)
		{
			m_Shader->SetDouble(m_DoubleProperties[i].Name, m_DoubleProperties[i].Property);
		}
	}

	void Material::SetBool(const std::string& name, bool value)
	{
		for (size_t i = 0; i < m_BoolProperties.size(); ++i)
		{
			if (m_BoolProperties[i].Name == name)
			{
				m_BoolProperties[i].Property = value;
				return;
			}
		}
	}

	void Material::SetInt(const std::string& name, int value)
	{
		for (size_t i = 0; i < m_IntProperties.size(); ++i)
		{
			if (m_IntProperties[i].Name == name)
			{
				m_IntProperties[i].Property = value;
				return;
			}
		}
	}

	void Material::SetFloat(const std::string& name, float value)
	{
		for (size_t i = 0; i < m_FloatProperties.size(); ++i)
		{
			if (m_FloatProperties[i].Name == name)
			{
				m_FloatProperties[i].Property = value;
				return;
			}
		}
	}

	void Material::SetVector2(const std::string& name, const Vector2& vec2)
	{
		for (size_t i = 0; i < m_Vector2Properties.size(); ++i)
		{
			if (m_Vector2Properties[i].Name == name)
			{
				m_Vector2Properties[i].Property = vec2;
				return;
			}
		}
	}

	void Material::SetVector3(const std::string& name, const Vector3& vec3)
	{
		for (size_t i = 0; i < m_Vector3Properties.size(); ++i)
		{
			if (m_Vector3Properties[i].Name == name)
			{
				m_Vector3Properties[i].Property = vec3;
				return;
			}
		}
	}

	void Material::SetVector4(const std::string& name, const Vector4& vec4)
	{
		for (size_t i = 0; i < m_Vector4Properties.size(); ++i)
		{
			if (m_Vector4Properties[i].Name == name)
			{
				m_Vector4Properties[i].Property = vec4;
				return;
			}
		}
	}

	void Material::SetColor(const std::string& name, const Color& color)
	{
		for (size_t i = 0; i < m_ColorProperties.size(); ++i)
		{
			if (m_ColorProperties[i].Name == name)
			{
				m_ColorProperties[i].Property = color;
				return;
			}
		}
	}

	void Material::SetMatrix3x3(const std::string& name, const Matrix3x3& mat3x3)
	{
		for (size_t i = 0; i < m_Matrix3x3Properties.size(); ++i)
		{
			if (m_Matrix3x3Properties[i].Name == name)
			{
				m_Matrix3x3Properties[i].Property = mat3x3;
				return;
			}
		}
	}

	void Material::SetMatrix4x4(const std::string& name, const Matrix4x4& mat4x4)
	{
		for (size_t i = 0; i < m_Matrix4x4Properties.size(); ++i)
		{
			if (m_Matrix4x4Properties[i].Name == name)
			{
				m_Matrix4x4Properties[i].Property = mat4x4;
				return;
			}
		}
	}

	void Material::SetTexture2D(const std::string& name, Texture2D* texture2D)
	{
		for (size_t i = 0; i < m_Texture2DProperties.size(); ++i)
		{
			if (m_Texture2DProperties[i].Name == name)
			{
				m_Texture2DProperties[i].Property = texture2D;
				return;
			}
		}
	}

	void Material::SetRenderTexture(const std::string& name, RenderTexture* renderTexture)
	{
		for (size_t i = 0; i < m_Texture2DProperties.size(); ++i)
		{
			if (m_Texture2DProperties[i].Name == name)
			{
				m_Texture2DProperties[i].Property = renderTexture;
				return;
			}
		}
	}

	void Material::SetCubeMap(const std::string& name, CubeMap* cubeMap)
	{
		for (size_t i = 0; i < m_CubeMapProperties.size(); ++i)
		{
			if (m_CubeMapProperties[i].Name == name)
			{
				m_CubeMapProperties[i].Property = cubeMap;
				return;
			}
		}
	}

	void Material::SetShader(Shader* shader)
	{
		m_Texture2DProperties.clear();
		m_ColorProperties.clear();
		m_Matrix3x3Properties.clear();
		m_Matrix4x4Properties.clear();
		m_Vector4Properties.clear();
		m_Vector3Properties.clear();
		m_Vector2Properties.clear();
		m_FloatProperties.clear();
		m_BoolProperties.clear();
		m_IntProperties.clear();
		m_UnsignedIntProperties.clear();
		m_DoubleProperties.clear();

		m_Shader = shader;

		std::vector<ShaderProperty> shaderProperties = m_Shader->GetShaderProperties();

		// TODO: In the future, default values will be assigned as specified through a shader file under "Properties"
		for (size_t i = 0; i < shaderProperties.size(); ++i)
		{
			switch (shaderProperties[i].GetPropertyType())
			{
			case ShaderPropertyEnumType::SAMPLERCUBE:

				m_CubeMapProperties.push_back(MaterialProperty<CubeMap*>(shaderProperties[i].GetName(), nullptr));
				break;

			case ShaderPropertyEnumType::SAMPLER2D:

				m_Texture2DProperties.push_back(MaterialProperty<Texture2D*>(shaderProperties[i].GetName(), nullptr));
				break;

			case ShaderPropertyEnumType::MAT4:

				m_Matrix4x4Properties.push_back(MaterialProperty<Matrix4x4>(shaderProperties[i].GetName(), Matrix4x4::Identity));
				break;

			case ShaderPropertyEnumType::MAT3:

				m_Matrix3x3Properties.push_back(MaterialProperty<Matrix3x3>(shaderProperties[i].GetName(), Matrix3x3::Identity));
				break;

			case ShaderPropertyEnumType::BOOL:

				m_BoolProperties.push_back(MaterialProperty<bool>(shaderProperties[i].GetName(), false));
				break;

			case ShaderPropertyEnumType::UNSIGNED_INT:

				m_UnsignedIntProperties.push_back(MaterialProperty<unsigned int>(shaderProperties[i].GetName(), 0));
				break;

			case ShaderPropertyEnumType::INT:

				m_IntProperties.push_back(MaterialProperty<int>(shaderProperties[i].GetName(), 0));
				break;

			case ShaderPropertyEnumType::DOUBLE:

				m_DoubleProperties.push_back(MaterialProperty<double>(shaderProperties[i].GetName(), 0.0));
				break;

			case ShaderPropertyEnumType::VEC4:

				m_Vector4Properties.push_back(MaterialProperty<Vector4>(shaderProperties[i].GetName(), Vector4::Zero));
				break;

			case ShaderPropertyEnumType::VEC3:

				m_Vector3Properties.push_back(MaterialProperty<Vector3>(shaderProperties[i].GetName(), Vector3::Zero));

				break;

			case ShaderPropertyEnumType::VEC2:

				m_Vector2Properties.push_back(MaterialProperty<Vector2>(shaderProperties[i].GetName(), Vector2::Zero));
				break;

			case ShaderPropertyEnumType::FLOAT:
				
				m_FloatProperties.push_back(MaterialProperty<float>(shaderProperties[i].GetName(), 0.0f));
				break;

			}
		}
	}

}