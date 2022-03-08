#pragma once

namespace OrbEngine
{
	enum class InternalFormat
	{
		COLOR,
		DEPTH_STENCIL
	};

	class RenderBuffer
	{
	public:
		/* Constructors/destructor */
		RenderBuffer(int width, int height, const InternalFormat& internalFormat);
		~RenderBuffer();

		/* Getters */
		unsigned int GetHandle() const { return m_RBO; }

	private:
		unsigned int m_RBO;
		int m_Width;
		int m_Height;
	};
}