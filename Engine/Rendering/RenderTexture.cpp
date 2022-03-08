#include "RenderTexture.h"

#include <glad/glad.h>

namespace OrbEngine
{
	RenderTexture::RenderTexture(int width, int height, const TextureFormat& textureFormat) :
		m_Width(width), m_Height(height), m_TextureFormat(textureFormat)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		// Initialize to default
		GLenum internalFormat = GL_RGB;
		GLenum format = GL_RGB;
		GLenum type = GL_UNSIGNED_INT;

		switch (m_TextureFormat)
		{
		case TextureFormat::COLOR:
			internalFormat = GL_RGB;
			format = GL_RGB;
			type = GL_UNSIGNED_INT;
			break;

		case TextureFormat::DEPTH_STENCIL:
			internalFormat = GL_DEPTH24_STENCIL8;
			format = GL_DEPTH_STENCIL;
			type = GL_UNSIGNED_INT_24_8;
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, type, nullptr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	RenderTexture::~RenderTexture()
	{
		glDeleteTextures(1, &m_Texture);
	}
}