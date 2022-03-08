#pragma once
#include "Component.h"

namespace OrbEngine
{
	/* Forward declarations */
	class Actor;
	class Material;
	class Mesh;

	class MeshRenderer : public Component
	{
	public:
		/* Constructors/destructor */
		MeshRenderer();
		~MeshRenderer();

		/* Main functions */

		/* Setters */
		void SetMesh(Mesh* mesh) { m_Mesh = mesh; }
		void SetMaterial(Material* material) { m_Material = material; }

		/* Getters */
		Mesh* GetMesh() const { return m_Mesh; }
		Material* GetMaterial() const { return m_Material; }

	private:
		Mesh* m_Mesh;
		Material* m_Material; // One material for now
	};

	class MeshRendererLessThanComparator
	{
	public:
		bool operator()(MeshRenderer* m1, MeshRenderer* m2);
	};
}