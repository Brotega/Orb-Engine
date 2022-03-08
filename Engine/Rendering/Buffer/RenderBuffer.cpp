#include "RenderBuffer.h"

#include <glad/glad.h>

namespace OrbEngine
{
	RenderBuffer::RenderBuffer(int width, int height, const InternalFormat& internalFormat) :
		m_RBO(0), m_Width(width), m_Height(height)
	{
		glGenRenderbuffers(1, &m_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		
		GLenum internFormat = GL_RGB;

		switch (internalFormat)
		{
		case InternalFormat::COLOR:
			internFormat = GL_RGB;
			break;

		case InternalFormat::DEPTH_STENCIL:
			internFormat = GL_DEPTH24_STENCIL8;
			break;
		}
		
		glRenderbufferStorage(GL_RENDERBUFFER, internFormat, m_Width, m_Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_RBO);
	}
}