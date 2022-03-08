#pragma once
#include "../Math/Math.h"
#include <vector>

namespace OrbEngine
{
	/* Forward declarations */
	class Application;
	class Transform;
	class VertexBuffer;
	struct VertexPosCol;

	class Shader;

	class Grid
	{
	public:
		/*Constructors/destructor */
		Grid(Application* application);
		Grid(Application* application, int rowCount, int colCount);
		~Grid();

		void Draw();

	private:
		std::vector<VertexPosCol> m_Grid;
		int m_RowCount;
		int m_ColCount;

		Application* m_Application;
		Transform* m_Transform;
		Shader* m_Shader;
		VertexBuffer* m_VertexBuffer;
	};
}