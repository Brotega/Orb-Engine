#pragma once
#include "../../Math/Math.h"
#include "../Color.h"

namespace OrbEngine
{
	struct VertexPos
	{
		Vector3 Position;
	};

	struct VertexPosCol
	{
		Vector3 Position;
		Color Colour;
	};

	struct VertexPosUV
	{
		Vector3 Position;
		Vector2 UV;
	};

	struct VertexPosColUV
	{
		Vector3 Position;
		Color Colour;
		Vector2 UV;
	};

	struct VertexPosNormTanBitUV
	{
		Vector3 Position;
		Vector3 Normal;
		Vector3 Tangent;
		Vector3 Bitangent;
		Vector2 UV;
	};
}