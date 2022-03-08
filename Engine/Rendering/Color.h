#pragma once

namespace OrbEngine
{
	class Color
	{
	public:
		float r, g, b, a;

		/* Constructors/destructor */
		Color();
		Color(float _r, float _g, float _b, float a = 1.0f);
		Color(const Color& color);
		~Color();

		Color& operator=(const Color& color);
		Color& operator*=(float val);
		friend Color operator*(const Color& color, float val);
		friend Color operator*(float val, const Color& color);

		/* Constants */
		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Purple;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Gray;
	};
}