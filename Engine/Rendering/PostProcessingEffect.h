#pragma once

namespace OrbEngine
{
	/* Forward declarations */
	class FrameBuffer;
	class IndexBuffer;
	class Material;
	class RenderBuffer;
	class RenderTexture;

	class PostProcessingEffect
	{
	public:
		/* Constructors/destructors */
		PostProcessingEffect();
		~PostProcessingEffect();

		/* Main functions */
		void CreateEffect(int width, int height, Material* material);
		void EnableFrameBuffer() const;
		void DisableFrameBuffer() const;
		void Render() const;


	private:
		FrameBuffer* m_FrameBuffer;
		IndexBuffer* m_IndexBuffer;
		RenderBuffer* m_RenderBuffer;
		RenderTexture* m_RenderTexture;
		Material* m_Material;
	};
}