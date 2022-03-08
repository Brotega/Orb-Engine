#pragma once

namespace OrbEngine
{
	namespace Math
	{
		inline constexpr float PI = 3.1415926535f;
		inline constexpr float Deg2Rad = PI / 180.0f;
		inline constexpr float Rad2Deg = 180.0f / PI;
		float Cos(const float& angle);
		float Sin(const float& angle);
		float Tan(const float& angle);
		float ACos(const float& val);
		float ASin(const float& val);
		float ATan(const float& val);
		float ATan2(const float& y, const float& x);
		float Abs(const float& val);
		float Sqrt(const float& val);
	}

	//----- 2D Float Vector -----
	class Vector2
	{
	public:
		// xy variables defining vector
		float x, y;

		// Constructors
		Vector2(); //Default
		explicit Vector2(float _x, float _y);
		Vector2(const Vector2& vec);

		void Set(float _x, float _y);
		float Length() const;
		float LengthSqr() const;
		void Normalize();

		// Overloads
		Vector2& operator=(const Vector2& vec);  // VecA = VecB (assignment)
		Vector2& operator+=(const Vector2& vec); // Vec2 += Vec2
		Vector2& operator-=(const Vector2& vec); // Vec2 -= Vec2
		Vector2& operator*=(float val);          // Vec2 *= scalar
		Vector2& operator*=(const Vector2& vec); // Vec2 *= Vec2 (component-wise multiplcation)
		Vector2& operator/=(float val);          // Vec2 /= scalar
		Vector2& operator/=(const Vector2& vec); // Vec2 /= Vec2 (component-wise division)
		friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs); // Vec2 + Vec2
		friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs); // Vec2 - Vec2
		friend Vector2 operator*(const Vector2& vec, float val);          // Vec2 * scalar
		friend Vector2 operator*(float val, const Vector2& vec);          // scalar * Vec2
		friend Vector2 operator/(const Vector2& vec, float val);          // Vec2 / scalar

		static float DotProduct(const Vector2& a, const Vector2& b);
		static Vector2 Normalize(const Vector2& vec);
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

		// Constants
		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 Left;
		static const Vector2 Right;
		static const Vector2 Up;
		static const Vector2 Down;

	};

	//----- 3D Float Vector -----
	class Vector3
	{
	public:
		// Member variables
		float x, y, z;

		// Constructors
		Vector3(); // Default
		explicit Vector3(float _x, float _y, float _z);
		Vector3(const Vector3& vec);

		Vector3& operator=(const Vector3& vec);  // Vec3 = Vec3 (assignment) 
		Vector3& operator+=(const Vector3& vec); // Vec3 += Vec3
		Vector3& operator-=(const Vector3& vec); // Vec3 -= Vec3
		Vector3& operator*=(float val);          // Vec3 *= scalar
		Vector3& operator*=(const Vector3& vec); // Vec3 *= Vec3 (component-wise multiplication)
		Vector3& operator/=(float val);          // Vec3 /= scalar
		Vector3& operator/=(const Vector3& vec); // Vec3 /= Vec3 (component-wise division)
		friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs); // Vec3 + Vec3
		friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs); // Vec3 - Vec3
		friend Vector3 operator*(const Vector3& vec, float val);          // Vec3 * scalar
		friend Vector3 operator*(float val, const Vector3& vec);          // scalar * Vec3
		friend Vector3 operator/(const Vector3& vec, float val);          // Vec3 / scalar

		void Set(float _x, float _y, float _z);
		float Length() const;
		float LengthSqr() const;
		void Normalize();

		static float DotProduct(const Vector3& a, const Vector3& b);
		static Vector3 CrossProduct(const Vector3& a, const Vector3& b);
		static Vector3 Normalize(const Vector3& vec); // A copy of vec gets created that's normalized and returned
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

		// Constants
		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Forward;
		static const Vector3 Backward;

	};

	//----- 4D Float Vector -----
	class Vector4
	{
	public:
		//xyzw variables
		float x, y, z, w;

		//Constructors
		Vector4();
		explicit Vector4(float _x, float _y, float _z, float _w);
		Vector4(const Vector4& vec);

		//Overloads
		Vector4& operator=(const Vector4& vec);
		Vector4& operator+=(const Vector4& vec);
		Vector4& operator-=(const Vector4& vec);
		Vector4& operator*=(float val);
		Vector4& operator*=(const Vector4& vec);
		Vector4& operator/=(float val);
		Vector4& operator/=(const Vector4& vec);
		friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
		friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
		friend Vector4 operator*(const Vector4& vec, float val);
		friend Vector4 operator*(float val, const Vector4& vec);
		friend Vector4 operator/(const Vector4& vec, float val);

		void Set(float _x, float _y, float _z, float _w);
		float Length() const;
		float LengthSqr() const;
		void Normalize();

		static float DotProduct(const Vector4& a, const Vector4& b);
		static Vector4 Normalize(const Vector4& vec);
		static Vector4 Lerp(const Vector4& a, const Vector4& b, float t);

		// Constants
		static const Vector4 Zero;
		static const Vector4 One;

	};

	class Matrix4x4;

	//----- 3x3 Float Matrix (Row Major) -----
	class Matrix3x3
	{
	public:
		//Variables
		float mat[3][3];

		//Constructors
		Matrix3x3(); //Default
		explicit Matrix3x3(const float _mat[3][3]);
		Matrix3x3(const Matrix3x3& _mat);

		//Overloads
		Matrix3x3& operator=(const Matrix3x3& _mat);
		Matrix3x3& operator=(const Matrix4x4& _mat);
		Matrix3x3& operator*=(const Matrix3x3& _mat);
		friend Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);
		friend Vector3 operator*(const Vector3& _vec, const Matrix3x3& _mat);

		// Main functions
		void Transpose();

		static Matrix3x3 CreateScaleMatrix(float x, float y);
		static Matrix3x3 CreateScaleMatrix(float size);
		static Matrix3x3 CreateRotationZMatrix(float theta);
		static Matrix3x3 CreateTranslationMatrix(float x, float y);

		//Constants
		static const Matrix3x3 Identity;

	};

	/* Forward declaration */
	class Quaternion;

	//----- 4x4 Float Matrix (Row Major) -----
	class Matrix4x4
	{
	public:
		//Variables
		float mat[4][4];

		//Constructors
		Matrix4x4(); //Default
		explicit Matrix4x4(const float _mat[4][4]);
		Matrix4x4(const Matrix4x4& _mat);

		//Overloads
		Matrix4x4& operator=(const Matrix4x4& _mat);
		Matrix4x4& operator=(const Matrix3x3& _mat);
		Matrix4x4& operator*=(const Matrix4x4& _mat);
		friend Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
		friend Vector4 operator*(const Vector4& _vec, const Matrix4x4& _mat);
		friend Vector3 operator*(const Vector3& _vec, const Matrix4x4& _mat);

		void Transpose();
		Quaternion ToQuaternion() const;

		Vector3 GetXAxis() const;
		Vector3 GetYAxis() const;
		Vector3 GetZAxis() const;

		static Matrix4x4 CreateScaleMatrix(float x, float y, float z);
		static Matrix4x4 CreateScaleMatrix(float size);
		static Matrix4x4 CreateScaleMatrix(const Vector3& vec3);
		static Matrix4x4 CreateRotationXMatrix(float theta);
		static Matrix4x4 CreateRotationYMatrix(float theta);
		static Matrix4x4 CreateRotationZMatrix(float theta);
		static Matrix4x4 CreateTranslationMatrix(float x, float y, float z);
		static Matrix4x4 CreateTranslationMatrix(const Vector3& vec3);
		static Matrix4x4 CreateLookAtMatrix(const Vector3& eye, const Vector3& target, const Vector3& _up);
		static Matrix4x4 CreateOrthographicMatrix(float width, float height, float zNear, float zFar);
		static Matrix4x4 CreatePerspectiveMatrix(float width, float height, float zNear, float zFar, float fov);

		//Constants
		static const Matrix4x4 Identity;

	};

	class Quaternion
	{
	public:
		// let u = <ux, uy, uz> be a unit rotation axis
		// q = cos(theta/2) + sin(theta/2)*ux*i + sin(theta/2)*uy*j + sin(theta/2)*uz*k
		float w, x, y, z; // q = w + xi + yj + zk

		Quaternion();
		Quaternion(const Vector3& axis, float angle);
		Quaternion(const float& qx, const float& qy, const float& qz, const float& qw);
		~Quaternion();

		Matrix4x4 ToMatrix4x4() const;
		void Conjugate();
		void Normalize();
		float MagnitudeSqr();
		float Magnitude();

		static Matrix4x4 CreateMatrix4x4(const Quaternion& q);
		static Quaternion AxisAngle(const Vector3& axis, float angle);

		static const Quaternion Identity;
	};
}