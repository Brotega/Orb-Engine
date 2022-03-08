#pragma once

#include "Texture2D.h"

namespace OrbEngine
{
	enum class TextureFormat
	{
		COLOR,
		DEPTH_STENCIL
	};

	class RenderTexture : public Texture2D
	{
	public:
		/* Constructors/destructor */
		RenderTexture(int width, int height, const TextureFormat& textureFormat);
		~RenderTexture();

		unsigned int GetHandle() const { return m_Texture; }

	private:
		int m_Width;
		int m_Height;
		TextureFormat m_TextureFormat;
	};
 }