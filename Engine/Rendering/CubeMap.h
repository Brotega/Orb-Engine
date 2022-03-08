#pragma once

#include <string>
#include <vector>

namespace OrbEngine
{
	class CubeMap
	{
	public:
		/* Constructors/destructor */
		CubeMap();
		~CubeMap();

		/* Main functions */
		bool Load(const std::vector<std::string>& filenames);
		void Bind() const;
		void SetActiveTexture(unsigned int slot) const;

	private:
		unsigned int m_Texture;
	};
}