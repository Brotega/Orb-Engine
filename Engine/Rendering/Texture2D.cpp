#include "Texture2D.h"

#include <Third Party/stb_image.h>
#include <glad/glad.h>

#include <iostream>

namespace OrbEngine
{
	Texture2D::Texture2D() :
		m_Texture(0), m_TextureType(TextureType::NONE)
	{
		
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_Texture);
	}

	Texture2D::Texture2D(const Texture2D& texture2D)
	{
		Load(texture2D.GetFilename(), texture2D.GetTextureType());
	}

	bool Texture2D::Load(const std::string& filename, TextureType textureType)
	{
		if (m_Texture != 0) glDeleteTextures(1, &m_Texture);

		m_Filename = filename;
		m_TextureType = textureType;

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(("Assets/Textures/" + filename).c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			switch (nrChannels)
			{
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
			default:
				break;
			}

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			return false;
		}

		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	void Texture2D::SetActiveTexture(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
}