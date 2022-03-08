#pragma once

namespace OrbEngine
{
	/* Forward declarations */
	class RenderBuffer;
	class RenderTexture;

	enum class AttachmentType
	{
		COLOR0,
		COLOR1,
		COLOR2,
		COLOR3,
		DEPTH,
		DEPTH_STENCIL,
		STENCIL
	};

	class FrameBuffer
	{
	public:
		/* Constructors/destructor */
		FrameBuffer(int width, int height);
		~FrameBuffer();

		/* Main functions */
		void AttachRenderTexture(RenderTexture* texture, const AttachmentType& attachmentType);
		void AttachRenderBuffer(RenderBuffer* renderBuffer, const AttachmentType& attachmentType);
		void Enable() const;
		void Disable() const;

	private:
		unsigned int m_FBO;
		int m_Width;
		int m_Height;

		unsigned int GetAttachmentType(const AttachmentType& attachmentType);
	};
}