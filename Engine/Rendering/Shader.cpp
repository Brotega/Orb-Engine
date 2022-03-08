#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"
#include <glad/glad.h>

#include "../Math/Math.h"
#include "../Rendering/Color.h"

namespace OrbEngine
{
    Shader::Shader(const Shader& shader)
    {
        m_ShaderID = shader.m_ShaderID;
    }

    Shader::Shader() :
        m_ShaderID(0)
    {

    }

    bool Shader::Load(const std::string& vertexFilename, const std::string& fragmentFilename)
    {
        std::string vertexCode;
        std::string fragmentCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        vShaderFile.open("Assets/Shaders/" + vertexFilename);
        fShaderFile.open("Assets/Shaders/" + fragmentFilename);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        if (!CheckCompileErrors(vertex, "VERTEX")) return false;

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        if (!CheckCompileErrors(fragment, "FRAGMENT")) return false;

        m_ShaderID = glCreateProgram();
        glAttachShader(m_ShaderID, vertex);
        glAttachShader(m_ShaderID, fragment);

        glLinkProgram(m_ShaderID);
        if (!CheckCompileErrors(fragment, "FRAGMENT")) return false;

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        GLenum properties[] =
        {
            GL_NAME_LENGTH,
            GL_TYPE,
            GL_LOCATION,
            GL_BLOCK_INDEX
        };


        int numUniforms = 0;
        glGetProgramInterfaceiv(m_ShaderID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

        for (int i = 0; i < numUniforms; ++i)
        {
            int results[4];
            glGetProgramResourceiv(m_ShaderID, GL_UNIFORM, i, 4, properties, 4, NULL, results);

            if (results[3] != -1) continue;

            int nameBufferSize = results[0] + 1;
            char* name = new char[nameBufferSize];

            glGetProgramResourceName(m_ShaderID, GL_UNIFORM, i, nameBufferSize, NULL, name);

            //printf("name: %s | type: %d | location: %d\n", name, results[1], results[2]);

            std::string nameStr(name);
            if (nameStr.find("materialProperty" != 0) || nameStr == "model")
            {
                FillInPropertiesFromGLType(name, results[1], results[2]);
            }

            delete[] name;
        }
        
        return true;
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ShaderID);
    }

    void Shader::Use()
    {
        glUseProgram(m_ShaderID);
    }

    void Shader::SetBool(const std::string& name, bool value) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform1i(m_ShaderProperties[i].GetUniformLocation(), (int)value);
                return;
            }
        }
        return;
    }

    void Shader::SetInt(const std::string& name, int value) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform1i(m_ShaderProperties[i].GetUniformLocation(), value);
                return;
            }
        }
        return;
    }

    void Shader::SetUnsignedInt(const std::string& name, unsigned int value) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform1ui(m_ShaderProperties[i].GetUniformLocation(), value);
                return;
            }
        }
        return;
    }

    void Shader::SetFloat(const std::string& name, float value) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform1f(m_ShaderProperties[i].GetUniformLocation(), value);
                return;
            }
        }
        return;
    }

    void Shader::SetDouble(const std::string& name, double value) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform1d(m_ShaderProperties[i].GetUniformLocation(), value);
                return;
            }
        }
        return;
    }

    void Shader::SetVector2(const std::string& name, const Vector2& vec2) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform2fv(m_ShaderProperties[i].GetUniformLocation(), 1, &vec2.x);
                return;
            }
        }
        return;
    }

    void Shader::SetVector3(const std::string& name, const Vector3& vec3) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform3fv(m_ShaderProperties[i].GetUniformLocation(), 1, &vec3.x);
                return;
            }
        }
        return;
    }

    void Shader::SetVector4(const std::string& name, const Vector4& vec4) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform4fv(m_ShaderProperties[i].GetUniformLocation(), 1, &vec4.x);
                return;
            }
        }
        return;
    }

    void Shader::SetColor(const std::string& name, const Color& color) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniform4fv(m_ShaderProperties[i].GetUniformLocation(), 1, &color.r);
                return;
            }
        }
        return;
    }


    void Shader::SetMatrix3x3(const std::string& name, const Matrix3x3& mat3) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniformMatrix3fv(m_ShaderProperties[i].GetUniformLocation(), 1, GL_FALSE, &mat3.mat[0][0]);
                return;
            }
        }
        return;
    }

    void Shader::SetMatrix4x4(const std::string& name, const Matrix4x4& mat4) const
    {
        for (size_t i = 0; i < m_ShaderProperties.size(); ++i)
        {
            if (m_ShaderProperties[i].GetName() == name)
            {
                glUniformMatrix4fv(m_ShaderProperties[i].GetUniformLocation(), 1, GL_FALSE, &mat4.mat[0][0]);
                return;
            }
        }
        return;
    }

    bool Shader::CheckCompileErrors(unsigned int shader, const char* type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog <<
                    "\n -- --------------------------------------------------- -- " << std::endl;

                return false;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog <<
                    "\n -- --------------------------------------------------- -- " << std::endl;

                return false;
            }
        }

        return true;
    }

    void Shader::FillInPropertiesFromGLType(const std::string& name, unsigned int type, int uniformLocation)
    {
        GLenum glType = static_cast<GLenum>(type);
        ShaderProperty shaderProperty;

        switch (glType)
        {
        case GL_FLOAT:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::FLOAT);
            break;
        case GL_FLOAT_VEC2:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::VEC2);
            break;
        case GL_FLOAT_VEC3:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::VEC3);
            break;
        case GL_FLOAT_VEC4:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::VEC4);
            break;
        case GL_DOUBLE:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::DOUBLE);
            break;
        case GL_INT:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::INT);
            break;
        case GL_UNSIGNED_INT:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::UNSIGNED_INT);
            break;
        case GL_BOOL:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::BOOL);
            break;
        case GL_FLOAT_MAT3:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::MAT3);
            break;
        case GL_FLOAT_MAT4:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::MAT4);
            break;
        case GL_SAMPLER_2D:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::SAMPLER2D);
            break;
        case GL_SAMPLER_3D:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::SAMPLER3D);
            break;
        case GL_SAMPLER_CUBE:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::SAMPLERCUBE);
            break;
        default:
            shaderProperty.SetPropertyType(ShaderPropertyEnumType::UNDEFINED);
            break;
        }

        shaderProperty.SetUniformLocation(uniformLocation);
        shaderProperty.SetName(name);
        m_ShaderProperties.push_back(shaderProperty);

        return;
    }
}