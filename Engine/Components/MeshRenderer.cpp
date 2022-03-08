#include "MeshRenderer.h"
#include "../Rendering/Material.h"

namespace OrbEngine
{
	MeshRenderer::MeshRenderer() :
		Component(), m_Mesh(nullptr), m_Material(nullptr)
	{

	}

	MeshRenderer::~MeshRenderer()
	{

	}

	bool MeshRendererLessThanComparator::operator()(MeshRenderer* m1, MeshRenderer* m2)
	{
		return m1->GetMaterial()->GetRenderQueue() < m2->GetMaterial()->GetRenderQueue();
	}
}