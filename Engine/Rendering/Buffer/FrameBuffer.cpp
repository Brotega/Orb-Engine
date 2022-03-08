#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "../RenderTexture.h"

#include <glad/glad.h>

namespace OrbEngine
{
	FrameBuffer::FrameBuffer(int width, int height) :
		m_FBO(0), m_Width(width), m_Height(height)
	{
		glGenFramebuffers(1, &m_FBO);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FBO);
	}

	void FrameBuffer::AttachRenderTexture(RenderTexture* texture, const AttachmentType& attachmentType)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GetAttachmentType(attachmentType), GL_TEXTURE_2D, texture->GetHandle(), 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::AttachRenderBuffer(RenderBuffer* renderBuffer, const AttachmentType& attachmentType)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GetAttachmentType(attachmentType), GL_RENDERBUFFER, renderBuffer->GetHandle());
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Enable() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void FrameBuffer::Disable() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int FrameBuffer::GetAttachmentType(const AttachmentType& attachmentType)
	{
		GLenum attachment = static_cast<GLenum>(attachmentType);

		switch (attachmentType)
		{
		case AttachmentType::COLOR0:
			attachment = GL_COLOR_ATTACHMENT0;
			break;

		case AttachmentType::COLOR1:
			attachment = GL_COLOR_ATTACHMENT1;
			break;

		case AttachmentType::COLOR2:
			attachment = GL_COLOR_ATTACHMENT2;
			break;

		case AttachmentType::COLOR3:
			attachment = GL_COLOR_ATTACHMENT3;
			break;

		case AttachmentType::DEPTH:
			attachment = GL_DEPTH_ATTACHMENT;
			break;

		case AttachmentType::DEPTH_STENCIL:
			attachment = GL_DEPTH_STENCIL_ATTACHMENT;
			break;

		case AttachmentType::STENCIL:
			attachment = GL_STENCIL_ATTACHMENT;
			break;
		}

		return attachment;
	}
}