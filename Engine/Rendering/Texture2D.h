#pragma once
#include <string>

namespace OrbEngine
{
	enum class TextureType
	{
		DEFAULT,
		NORMAL,
		NONE
	};

	class Texture2D
	{
	public:
		/* Constructors/destructor */
		Texture2D();
		~Texture2D();
		Texture2D(const Texture2D& texture2D);

		/* Main functions */
		bool Load(const std::string& filename, TextureType textureType);
		void Bind() const;
		void SetActiveTexture(unsigned int slot) const;

		/* Getters */
		TextureType GetTextureType() const { return m_TextureType; }
		std::string GetFilename() const { return m_Filename; }

	protected:
		unsigned int m_Texture;

	private:
		TextureType m_TextureType;
		std::string m_Filename;
	};
}