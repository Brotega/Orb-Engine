#include "Utility.h"

namespace OrbEngine
{
	Utility::Utility()
	{

	}

	Utility::~Utility()
	{

	}

	float Utility::Min(float val1, float val2)
	{
		if (val1 <= val2) return val1;
		else return val2;
	}

	float Utility::Max(float val1, float val2)
	{
		if (val1 >= val2) return val1;
		else return val2;
	}
}