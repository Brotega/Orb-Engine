#pragma once
#include "../../Math/Math.h"
#include "../Color.h"

namespace OrbEngine
{
	struct CameraUniform // 148
	{
		Matrix4x4 View;        // 64, 0
		Matrix4x4 Projection;  // 64, 64
		Vector3 Position; //WS // 12, 128
		float ZNear;           //  4, 140
		float ZFar;            //  4, 144 -> 148
	};

	struct LightingUniform // 512
	{
		// Directional Light - 80
		Vector3 DLDirection; float Pad0; // 16, 0
		Color DLAmbient;                 // 16, 16
		Color DLDiffuse;                 // 16, 32
		Color DLSpecular;                // 16, 48
		bool DLIsEnabled;                //  1, 64
		bool Pad1, Pad2, Pad3;           //  3, 65
		Vector3 Pad4;                    // 12, 68 -> 80

		// Spot Light - 112
		Vector3 SLPosition;  float Pad5; // 16, 80
		Vector3 SLDirection; float Pad6; // 16, 96
		Color SLAmbient;                 // 16, 112
		Color SLDiffuse;                 // 16, 128
		Color SLSpecular;                // 16, 144
		float SLInnerAngle;              //  4, 160
		float SLOuterAngle;              //  4, 164
		float SLConstant;                //  4, 168
		float SLLinear;                  //  4, 172
		float SLQuadratic;               //  4, 176
		bool SLIsEnabled;                //  1, 180
		bool Pad8, Pad9, Pad10;          //  3, 181
		Vector2 Pad7;                    //  8, 184 -> 192

		// Point Light 1 - 80
		Vector3 PLPosition1; float Pad11; // 16, 192
		Color PLAmbient1;                 // 16, 208
		Color PLDiffuse1;                 // 16, 224
		Color PLSpecular1;                // 16, 240
		float PLConstant1;                //  4, 256
		float PLLinear1;                  //  4, 260
		float PLQuadratic1;               //  4, 264
		bool PLIsEnabled1;                //  1, 268
		bool Pad12, Pad13, Pad14;         //  3, 269 -> 272

		// Point Light 2 - 80
		Vector3 PLPosition2; float Pad15; // 16, 272
		Color PLAmbient2;                 // 16, 288
		Color PLDiffuse2;                 // 16, 304
		Color PLSpecular2;                // 16, 320
		float PLConstant2;                //  4, 336
		float PLLinear2;                  //  4, 340
		float PLQuadratic2;               //  4, 344
		bool PLIsEnabled2;                //  1, 348
		bool Pad16, Pad17, Pad18;         //  3, 349 -> 352

		// Point Light 3 - 80
		Vector3 PLPosition3; float Pad19; // 16, 352
		Color PLAmbient3;                 // 16, 368
		Color PLDiffuse3;                 // 16, 384
		Color PLSpecular3;                // 16, 400
		float PLConstant3;                //  4, 416
		float PLLinear3;                  //  4, 420
		float PLQuadratic3;               //  4, 424
		bool PLIsEnabled3;                //  1, 428
		bool Pad20, Pad21, Pad22;         //  3, 429 -> 432

		// Point Light 4 - 80
		Vector3 PLPosition4; float Pad23; // 16, 432
		Color PLAmbient4;                 // 16, 448
		Color PLDiffuse4;                 // 16, 464
		Color PLSpecular4;                // 16, 480
		float PLConstant4;                //  4, 496
		float PLLinear4;                  //  4, 500
		float PLQuadratic4;               //  4, 504
		bool PLIsEnabled4;                //  1, 508
		bool Pad24, Pad25, Pad26;         //  3, 509 -> 512
	};

	class UniformBuffer
	{
	public:
		/* Constructors/destructor */
		UniformBuffer(int bindPoint, int byteSize);
		~UniformBuffer();

		/* Main functions */
		void UpdateBuffer(int offset, int size, const void* data);

	private:
		unsigned int m_UBO;
		unsigned int m_BindPoint;
	};
}