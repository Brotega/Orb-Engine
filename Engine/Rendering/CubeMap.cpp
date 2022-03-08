#include "CubeMap.h"

#include <Third Party/stb_image.h>
#include <glad/glad.h>

#include <iostream>

namespace OrbEngine
{
	CubeMap::CubeMap() :
		m_Texture(0)
	{
		
	}

	CubeMap::~CubeMap()
	{
		
	}

	bool CubeMap::Load(const std::vector<std::string>& filenames)
	{
		if (m_Texture != 0) glDeleteTextures(1, &m_Texture);

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);

		int width, height, nrChannels;
		unsigned char* data;

		stbi_set_flip_vertically_on_load(false);

		for (size_t i = 0; i < filenames.size(); ++i)
		{
			data = stbi_load(("Assets/Cubemaps/" + filenames[i]).c_str(), &width, &height, &nrChannels, 0);

			if (data)
			{
				switch (nrChannels)
				{
				case 3:
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					break;

				case 4:
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + static_cast<int>(i), 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					break;
				}
			}
			else
			{
				std::cout << "Failed to load texture" << std::endl;
				return false;
			}

			stbi_image_free(data);
		}

		stbi_set_flip_vertically_on_load(true);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return true;
	}

	void CubeMap::SetActiveTexture(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
	}

	void CubeMap::Bind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
	}
}