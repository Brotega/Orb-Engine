#include "PostProcessingEffect.h"
#include "RenderTexture.h"
#include "Material.h"
#include "Buffer/FrameBuffer.h"
#include "Buffer/RenderBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/VertexTypes.h"
#include "../Math/Math.h"

namespace OrbEngine
{
	PostProcessingEffect::PostProcessingEffect() :
		m_FrameBuffer(nullptr), m_IndexBuffer(nullptr), m_RenderBuffer(nullptr), m_RenderTexture(nullptr), m_Material(nullptr)
	{
		
	}

	PostProcessingEffect::~PostProcessingEffect()
	{
		delete m_FrameBuffer;
		delete m_RenderBuffer;
		delete m_RenderTexture;
		delete m_IndexBuffer;
	}

	void PostProcessingEffect::CreateEffect(int width, int height, Material* material)
	{
		m_Material = material;
		m_FrameBuffer = new FrameBuffer(width, height);
		m_RenderBuffer = new RenderBuffer(width, height, InternalFormat::DEPTH_STENCIL);
		m_RenderTexture = new RenderTexture(width, height, TextureFormat::COLOR);
		m_FrameBuffer->AttachRenderBuffer(m_RenderBuffer, AttachmentType::DEPTH_STENCIL);
		m_FrameBuffer->AttachRenderTexture(m_RenderTexture, AttachmentType::COLOR0);

		std::vector<VertexPosUV> vertices
		{
			{Vector3(-1.0f,  1.0f, 0.0f), Vector2(0.0f, 1.0f)}, // Top left
			{Vector3(-1.0f, -1.0f, 0.0f), Vector2(0.0f, 0.0f)}, // Bottom Left
			{Vector3( 1.0f,  1.0f, 0.0f), Vector2(1.0f, 1.0f)}, // Top right
			{Vector3( 1.0f, -1.0f, 0.0f), Vector2(1.0f, 0.0f)}  // Bottom right
		};

		std::vector<unsigned int> indices
		{
			0, 1, 2,
			1, 3, 2
		};

		m_IndexBuffer = new IndexBuffer(vertices, indices);
	}

	void PostProcessingEffect::EnableFrameBuffer() const
	{
		m_FrameBuffer->Enable();
	}

	void PostProcessingEffect::DisableFrameBuffer() const
	{
		m_FrameBuffer->Disable();
	}

	void PostProcessingEffect::Render() const
	{
		if (!m_Material) return;

		m_Material->UseShader();
		m_Material->SetRenderTexture("materialProperty.Texture", m_RenderTexture);
		m_Material->SetProperties();
		m_IndexBuffer->Draw();
	}
}