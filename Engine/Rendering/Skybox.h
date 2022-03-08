#pragma once

namespace OrbEngine
{
	/* Forward declarations */
	class VertexBuffer;
	class Material;

	class Skybox
	{
	public:
		/* Constructors/ destructor */
		Skybox();
		~Skybox();

		/* Main functions */
		void Draw() const;

		/* Setters */
		void SetMaterial(Material* material) { m_Material = material; }

	private:
		VertexBuffer* m_VertexBuffer;
		Material* m_Material;
	};
}