#include "Color.h"

#include "../Utility/Utility.h"

namespace OrbEngine
{
	//----- Define Color constants ------
	const Color Color::White(1.0f, 1.0f, 1.0f);
	const Color Color::Black(0.0f, 0.0f, 0.0f);
	const Color Color::Red(1.0f, 0.0f, 0.0f);
	const Color Color::Green(0.0f, 1.0f, 0.0f);
	const Color Color::Blue(0.0f, 0.0f, 1.0f);
	const Color Color::Purple(1.0f, 0.0f, 1.0f);
	const Color Color::Yellow(1.0f, 1.0f, 0.0f);
	const Color Color::Cyan(0.0f, 1.0f, 1.0f);
	const Color Color::Gray(0.5f, 0.5f, 0.5f);
	//-------------------------------------

	Color::Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
	{

	}

	Color::Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a)
	{

	}

	Color::Color(const Color& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}

	Color& Color::operator*=(float val)
	{
		r *= val;
		g *= val;
		b *= val;

		return *this;
	}

	Color& Color::operator=(const Color& color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;

		return *this;
	}

	Color operator*(const Color& color, float val)
	{
		return Color(color.r * val, color.g * val, color.b * val);
	}

	Color operator*(float val, const Color& color)
	{
		return Color(color.r * val, color.g * val, color.b * val);
	}

	Color::~Color()
	{

	}
}