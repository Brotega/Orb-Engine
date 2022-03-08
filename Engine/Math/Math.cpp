#include "Math.h"
#include <cmath>

namespace OrbEngine
{
	namespace Math
	{
		float Cos(const float& angle) { return cosf(angle); }
		float Sin(const float& angle) { return sinf(angle); }
		float Tan(const float& angle) { return tanf(angle); }
		float ACos(const float& val) { return acosf(val); }
		float ASin(const float& val) { return asinf(val); }
		float ATan(const float& val) { return atanf(val); }
		float ATan2(const float& y, const float& x) { return atan2f(y, x); }
		float Abs(const float& val) { return abs(val); }
		float Sqrt(const float& val) { return sqrtf(val); }
	}

	//----- Define Vector2 constants ------
	const Vector2 Vector2::Zero(0.0f, 0.0f);
	const Vector2 Vector2::One(1.0f, 1.0f);
	const Vector2 Vector2::Left(1.0f, 0.0f);
	const Vector2 Vector2::Right(-1.0f, 0.0f);
	const Vector2 Vector2::Up(0.0f, 1.0f);
	const Vector2 Vector2::Down(0.0f, -1.0f);
	//-------------------------------------

	Vector2::Vector2() : x(0.0f), y(0.0f)
	{

	}

	Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
	{

	}

	Vector2::Vector2(const Vector2& vec)
	{
		x = vec.x;
		y = vec.y;
	}

	Vector2& Vector2::operator=(const Vector2& vec)
	{
		x = vec.x;
		y = vec.y;
		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	Vector2& Vector2::operator*=(float val)
	{
		x *= val;
		y *= val;
		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& vec)
	{
		x *= vec.x;
		y *= vec.y;
		return *this;
	}

	Vector2& Vector2::operator/=(float val)
	{
		x /= val;
		y /= val;
		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& vec)
	{
		x /= vec.x;
		y /= vec.y;
		return *this;
	}

	Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	Vector2 operator*(const Vector2& vec, float val)
	{
		return Vector2(vec.x * val, vec.y * val);
	}

	Vector2 operator*(float val, const Vector2& vec)
	{
		return Vector2(vec.x * val, vec.y * val);
	}

	Vector2 operator/(const Vector2& vec, float val)
	{
		return Vector2(vec.x / val, vec.y / val);
	}

	void Vector2::Set(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float Vector2::Length() const
	{
		return Math::Sqrt(LengthSqr());
	}

	float Vector2::LengthSqr() const
	{
		return x * x + y * y;
	}

	void Vector2::Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	float Vector2::DotProduct(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	Vector2 Vector2::Normalize(const Vector2& vec)
	{
		Vector2 copyVec = vec;
		copyVec.Normalize();
		return copyVec;
	}

	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(a + (b - a) * t);
	}

	//----- Define Vector3 constants ------
	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
	const Vector3 Vector3::Left(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Right(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::Forward(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::Backward(0.0f, 0.0f, -1.0f);
	//-------------------------------------

	Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f)
	{

	}

	Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
	{

	}

	Vector3::Vector3(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	Vector3& Vector3::operator=(const Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector3& Vector3::operator*=(float val)
	{
		x *= val;
		y *= val;
		z *= val;
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}

	Vector3& Vector3::operator/=(float val)
	{
		x /= val;
		y /= val;
		z /= val;
		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& vec)
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}

	Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	Vector3 operator*(const Vector3& vec, float val)
	{
		return Vector3(vec.x * val, vec.y * val, vec.z * val);
	}

	Vector3 operator*(float val, const Vector3& vec)
	{
		return Vector3(vec.x * val, vec.y * val, vec.z * val);
	}

	Vector3 operator/(const Vector3& vec, float val)
	{
		return Vector3(vec.x / val, vec.y / val, vec.z / val);
	}

	void Vector3::Set(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float Vector3::Length() const
	{
		return Math::Sqrt(LengthSqr());
	}

	float Vector3::LengthSqr() const
	{
		return x * x + y * y + z * z;
	}

	void Vector3::Normalize()
	{
		float length = Length();
		if (length == 0.0f) return; 
		x /= length;
		y /= length;
		z /= length;
	}

	float Vector3::DotProduct(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& b)
	{
		float x = a.y * b.z - a.z * b.y;
		float y = a.z * b.x - a.x * b.z;
		float z = a.x * b.y - a.y * b.x;
		return Vector3(x, y, z);
	}

	Vector3 Vector3::Normalize(const Vector3& vec)
	{
		Vector3 copyVec = vec;
		copyVec.Normalize();
		return copyVec;
	}

	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
	{
		return Vector3(a + (b - a) * t);
	}

	//----- Define Vector4 constants ------
	const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);
	//-------------------------------------


	Vector4::Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{

	}

	Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
	{

	}

	Vector4::Vector4(const Vector4& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
	}

	//Overloads
	Vector4& Vector4::operator=(const Vector4& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;
		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		w += vec.w;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}

	Vector4& Vector4::operator*=(float val)
	{
		x *= val;
		y *= val;
		z *= val;
		w *= val;
		return *this;
	}

	Vector4& Vector4::operator*=(const Vector4& vec)
	{
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		w *= vec.w;
		return *this;
	}

	Vector4& Vector4::operator/=(float val)
	{
		x /= val;
		y /= val;
		z /= val;
		w /= val;
		return *this;
	}

	Vector4& Vector4::operator/=(const Vector4& vec)
	{
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		w /= vec.w;
		return *this;
	}

	Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	Vector4 operator*(const Vector4& vec, float val)
	{
		return Vector4(vec.x * val, vec.y * val, vec.z * val, vec.w * val);
	}

	Vector4 operator*(float val, const Vector4& vec)
	{
		return Vector4(vec.x * val, vec.y * val, vec.z * val, vec.w * val);
	}

	Vector4 operator/(const Vector4& vec, float val)
	{
		return Vector4(vec.x / val, vec.y / val, vec.z / val, vec.w / val);
	}

	void Vector4::Set(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	float Vector4::Length() const
	{
		return Math::Sqrt(LengthSqr());
	}

	float Vector4::LengthSqr() const
	{
		return x * x + y * y + z * z + w * w;
	}

	void Vector4::Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}

	float Vector4::DotProduct(const Vector4& a, const Vector4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	Vector4 Vector4::Normalize(const Vector4& vec)
	{
		Vector4 copyVec = vec;
		copyVec.Normalize();
		return copyVec;
	}

	Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float t)
	{
		return Vector4(a + (b - a) * t);
	}

	//----- Define Matrix3x3 constants ------
	const float idMatrix3x3[3][3] =
	{
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f}
	};

	const Matrix3x3 Matrix3x3::Identity(idMatrix3x3);
	//-------------------------------------

	Matrix3x3::Matrix3x3()
	{
		*this = Matrix3x3::Identity;
	}

	Matrix3x3::Matrix3x3(const float _mat[3][3])
	{
		memcpy(mat, _mat, 9 * sizeof(float));
	}

	Matrix3x3::Matrix3x3(const Matrix3x3& _mat)
	{
		memcpy(mat, _mat.mat, 9 * sizeof(float));
	}

	Matrix3x3& Matrix3x3::operator=(const Matrix3x3& _mat)
	{
		memcpy(mat, _mat.mat, 9 * sizeof(float));
		return *this;
	}

	Matrix3x3& Matrix3x3::operator=(const Matrix4x4& _mat)
	{
		mat[0][0] = _mat.mat[0][0];
		mat[0][1] = _mat.mat[0][1];
		mat[0][2] = _mat.mat[0][2];
		mat[1][0] = _mat.mat[1][0];
		mat[1][1] = _mat.mat[1][1];
		mat[1][2] = _mat.mat[1][2];
		mat[2][0] = _mat.mat[2][0];
		mat[2][1] = _mat.mat[2][1];
		mat[2][2] = _mat.mat[2][2];

		return *this;
	}

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& _mat)
	{
		*this = *this * _mat;
		return *this;
	}

	Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 mat3x3;

		// column 0 
		mat3x3.mat[0][0] =
			lhs.mat[0][0] * rhs.mat[0][0] +
			lhs.mat[0][1] * rhs.mat[1][0] +
			lhs.mat[0][2] * rhs.mat[2][0];

		mat3x3.mat[1][0] =
			lhs.mat[1][0] * rhs.mat[0][0] +
			lhs.mat[1][1] * rhs.mat[1][0] +
			lhs.mat[1][2] * rhs.mat[2][0];

		mat3x3.mat[2][0] =
			lhs.mat[2][0] * rhs.mat[0][0] +
			lhs.mat[2][1] * rhs.mat[1][0] +
			lhs.mat[2][2] * rhs.mat[2][0];

		// column 1
		mat3x3.mat[0][1] =
			lhs.mat[0][0] * rhs.mat[0][1] +
			lhs.mat[0][1] * rhs.mat[1][1] +
			lhs.mat[0][2] * rhs.mat[2][1];

		mat3x3.mat[1][1] =
			lhs.mat[1][0] * rhs.mat[0][1] +
			lhs.mat[1][1] * rhs.mat[1][1] +
			lhs.mat[1][2] * rhs.mat[2][1];

		mat3x3.mat[2][1] =
			lhs.mat[2][0] * rhs.mat[0][1] +
			lhs.mat[2][1] * rhs.mat[1][1] +
			lhs.mat[2][2] * rhs.mat[2][1];

		// column 2
		mat3x3.mat[0][2] =
			lhs.mat[0][0] * rhs.mat[0][2] +
			lhs.mat[0][1] * rhs.mat[1][2] +
			lhs.mat[0][2] * rhs.mat[2][2];

		mat3x3.mat[1][2] =
			lhs.mat[1][0] * rhs.mat[0][2] +
			lhs.mat[1][1] * rhs.mat[1][2] +
			lhs.mat[1][2] * rhs.mat[2][2];

		mat3x3.mat[2][2] =
			lhs.mat[2][0] * rhs.mat[0][2] +
			lhs.mat[2][1] * rhs.mat[1][2] +
			lhs.mat[2][2] * rhs.mat[2][2];


		return mat3x3;
	}

	Vector3 operator*(const Vector3& _vec, const Matrix3x3& _mat3x3)
	{
		float x =
			_mat3x3.mat[0][0] * _vec.x +
			_mat3x3.mat[1][0] * _vec.y +
			_mat3x3.mat[2][0] * _vec.z;

		float y =
			_mat3x3.mat[0][1] * _vec.x +
			_mat3x3.mat[1][1] * _vec.y +
			_mat3x3.mat[2][1] * _vec.z;

		float z =
			_mat3x3.mat[0][2] * _vec.x +
			_mat3x3.mat[1][2] * _vec.y +
			_mat3x3.mat[2][2] * _vec.z;

		return Vector3(x, y, z);
	}

	void Matrix3x3::Transpose()
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = i; j < 3; ++j)
			{
				float temp = mat[i][j];
				mat[i][j] = mat[j][i];
				mat[j][i] = temp;
			}
		}
	}

	Matrix3x3 Matrix3x3::CreateScaleMatrix(float x, float y)
	{
		float mat[3][3] =
		{
			{x, 0.0f, 0.0f},
			{0.0f, y, 0.0f},
			{0.0f, 0.0f, 1.0f},
		};
		return Matrix3x3(mat);
	}

	Matrix3x3 Matrix3x3::CreateScaleMatrix(float size)
	{
		return CreateScaleMatrix(size, size);
	}

	Matrix3x3 Matrix3x3::CreateRotationZMatrix(float theta)
	{
		float mat[3][3] =
		{
			{ cosf(theta), sinf(theta), 0.0f},
			{-sinf(theta), cosf(theta), 0.0f},
			{        0.0f,        0.0f, 1.0f}
		};
		return Matrix3x3(mat);
	}

	Matrix3x3 Matrix3x3::CreateTranslationMatrix(float x, float y)
	{
		float mat[3][3] =
		{
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{   x,    y, 1.0f}
		};
		return Matrix3x3(mat);
	}

	//----- Define Matrix4x4 constants ------
	const float idMatrix4x4[4][4] =
	{
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};

	const Matrix4x4 Matrix4x4::Identity(idMatrix4x4);
	//-------------------------------------

	Matrix4x4::Matrix4x4()
	{
		*this = Matrix4x4::Identity;
	}

	Matrix4x4::Matrix4x4(const float _mat[4][4])
	{
		memcpy(mat, _mat, 16 * sizeof(float));
	}

	Matrix4x4::Matrix4x4(const Matrix4x4& _mat)
	{
		memcpy(mat, _mat.mat, 16 * sizeof(float));
	}

	Matrix4x4& Matrix4x4::operator=(const Matrix4x4& _mat)
	{
		memcpy(mat, _mat.mat, 16 * sizeof(float));
		return *this;
	}

	Matrix4x4& Matrix4x4::operator=(const Matrix3x3& _mat)
	{
		mat[0][0] = _mat.mat[0][0];
		mat[0][1] = _mat.mat[0][1];
		mat[0][2] = _mat.mat[0][2];
		mat[0][3] = 0.0f;

		mat[1][0] = _mat.mat[1][0];
		mat[1][1] = _mat.mat[1][1];
		mat[1][2] = _mat.mat[1][2];
		mat[1][3] = 0.0f;

		mat[2][0] = _mat.mat[2][0];
		mat[2][1] = _mat.mat[2][0];
		mat[2][2] = _mat.mat[2][0];
		mat[2][3] = 0.0f;

		mat[3][0] = 0.0f;
		mat[3][1] = 0.0f;
		mat[3][2] = 0.0f;
		mat[3][3] = 0.0f;

		return *this;
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& _mat)
	{
		*this = *this * _mat;
		return *this;
	}

	Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 mat4x4;

		// column 0 
		mat4x4.mat[0][0] =
			lhs.mat[0][0] * rhs.mat[0][0] +
			lhs.mat[0][1] * rhs.mat[1][0] +
			lhs.mat[0][2] * rhs.mat[2][0] +
			lhs.mat[0][3] * rhs.mat[3][0];

		mat4x4.mat[1][0] =
			lhs.mat[1][0] * rhs.mat[0][0] +
			lhs.mat[1][1] * rhs.mat[1][0] +
			lhs.mat[1][2] * rhs.mat[2][0] +
			lhs.mat[1][3] * rhs.mat[3][0];

		mat4x4.mat[2][0] =
			lhs.mat[2][0] * rhs.mat[0][0] +
			lhs.mat[2][1] * rhs.mat[1][0] +
			lhs.mat[2][2] * rhs.mat[2][0] +
			lhs.mat[2][3] * rhs.mat[3][0];

		mat4x4.mat[3][0] =
			lhs.mat[3][0] * rhs.mat[0][0] +
			lhs.mat[3][1] * rhs.mat[1][0] +
			lhs.mat[3][2] * rhs.mat[2][0] +
			lhs.mat[3][3] * rhs.mat[3][0];

		// column 1
		mat4x4.mat[0][1] =
			lhs.mat[0][0] * rhs.mat[0][1] +
			lhs.mat[0][1] * rhs.mat[1][1] +
			lhs.mat[0][2] * rhs.mat[2][1] +
			lhs.mat[0][3] * rhs.mat[3][1];

		mat4x4.mat[1][1] =
			lhs.mat[1][0] * rhs.mat[0][1] +
			lhs.mat[1][1] * rhs.mat[1][1] +
			lhs.mat[1][2] * rhs.mat[2][1] +
			lhs.mat[1][3] * rhs.mat[3][1];

		mat4x4.mat[2][1] =
			lhs.mat[2][0] * rhs.mat[0][1] +
			lhs.mat[2][1] * rhs.mat[1][1] +
			lhs.mat[2][2] * rhs.mat[2][1] +
			lhs.mat[2][3] * rhs.mat[3][1];

		mat4x4.mat[3][1] =
			lhs.mat[3][0] * rhs.mat[0][1] +
			lhs.mat[3][1] * rhs.mat[1][1] +
			lhs.mat[3][2] * rhs.mat[2][1] +
			lhs.mat[3][3] * rhs.mat[3][1];

		// column 2
		mat4x4.mat[0][2] =
			lhs.mat[0][0] * rhs.mat[0][2] +
			lhs.mat[0][1] * rhs.mat[1][2] +
			lhs.mat[0][2] * rhs.mat[2][2] +
			lhs.mat[0][3] * rhs.mat[3][2];

		mat4x4.mat[1][2] =
			lhs.mat[1][0] * rhs.mat[0][2] +
			lhs.mat[1][1] * rhs.mat[1][2] +
			lhs.mat[1][2] * rhs.mat[2][2] +
			lhs.mat[1][3] * rhs.mat[3][2];

		mat4x4.mat[2][2] =
			lhs.mat[2][0] * rhs.mat[0][2] +
			lhs.mat[2][1] * rhs.mat[1][2] +
			lhs.mat[2][2] * rhs.mat[2][2] +
			lhs.mat[2][3] * rhs.mat[3][2];

		mat4x4.mat[3][2] =
			lhs.mat[3][0] * rhs.mat[0][2] +
			lhs.mat[3][1] * rhs.mat[1][2] +
			lhs.mat[3][2] * rhs.mat[2][2] +
			lhs.mat[3][3] * rhs.mat[3][2];

		// column 3
		mat4x4.mat[0][3] =
			lhs.mat[0][0] * rhs.mat[0][3] +
			lhs.mat[0][1] * rhs.mat[1][3] +
			lhs.mat[0][2] * rhs.mat[2][3] +
			lhs.mat[0][3] * rhs.mat[3][3];

		mat4x4.mat[1][3] =
			lhs.mat[1][0] * rhs.mat[0][3] +
			lhs.mat[1][1] * rhs.mat[1][3] +
			lhs.mat[1][2] * rhs.mat[2][3] +
			lhs.mat[1][3] * rhs.mat[3][3];

		mat4x4.mat[2][3] =
			lhs.mat[2][0] * rhs.mat[0][3] +
			lhs.mat[2][1] * rhs.mat[1][3] +
			lhs.mat[2][2] * rhs.mat[2][3] +
			lhs.mat[2][3] * rhs.mat[3][3];

		mat4x4.mat[3][3] =
			lhs.mat[3][0] * rhs.mat[0][3] +
			lhs.mat[3][1] * rhs.mat[1][3] +
			lhs.mat[3][2] * rhs.mat[2][3] +
			lhs.mat[3][3] * rhs.mat[3][3];

		return mat4x4;
	}

	Vector4 operator*(const Vector4& _vec, const Matrix4x4& _mat4x4)
	{
		float x =
			_mat4x4.mat[0][0] * _vec.x +
			_mat4x4.mat[1][0] * _vec.y +
			_mat4x4.mat[2][0] * _vec.z +
			_mat4x4.mat[3][0] * _vec.w;

		float y =
			_mat4x4.mat[0][1] * _vec.x +
			_mat4x4.mat[1][1] * _vec.y +
			_mat4x4.mat[2][1] * _vec.z +
			_mat4x4.mat[3][1] * _vec.w;

		float z =
			_mat4x4.mat[0][2] * _vec.x +
			_mat4x4.mat[1][2] * _vec.y +
			_mat4x4.mat[2][2] * _vec.z +
			_mat4x4.mat[3][2] * _vec.w;

		float w =
			_mat4x4.mat[0][3] * _vec.x +
			_mat4x4.mat[1][3] * _vec.y +
			_mat4x4.mat[2][3] * _vec.z +
			_mat4x4.mat[3][3] * _vec.w;

		return Vector4(x, y, z, w);
	}

	Vector3 operator*(const Vector3& _vec, const Matrix4x4& _mat4x4)
	{

		float x =
			_mat4x4.mat[0][0] * _vec.x +
			_mat4x4.mat[1][0] * _vec.y +
			_mat4x4.mat[2][0] * _vec.z;

		float y =
			_mat4x4.mat[0][1] * _vec.x +
			_mat4x4.mat[1][1] * _vec.y +
			_mat4x4.mat[2][1] * _vec.z;

		float z =
			_mat4x4.mat[0][2] * _vec.x +
			_mat4x4.mat[1][2] * _vec.y +
			_mat4x4.mat[2][2] * _vec.z;

		return Vector3(x, y, z);
	}

	void Matrix4x4::Transpose()
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = i; j < 4; ++j)
			{
				float temp = mat[i][j];
				mat[i][j] = mat[j][i];
				mat[j][i] = temp;
			}
		}
	}

	Quaternion Matrix4x4::ToQuaternion() const
	{
		float tr = mat[0][0] + mat[1][1] + mat[2][2];

		float qw = 0;
		float qx = 0;
		float qy = 0;
		float qz = 0;

		if (tr > 0)
		{
			float S = Math::Sqrt(tr + 1.0f) * 2.0f;
			qw = 0.25f * S;
			qx = (mat[1][2] - mat[2][1]) / S;
			qy = (mat[2][0] - mat[0][2]) / S;
			qz = (mat[0][1] - mat[1][0]) / S;
		}
		else if ((mat[0][0] > mat[1][1]) && (mat[0][0] > mat[2][2]))
		{
			float S = Math::Sqrt(1.0f + mat[0][0] - mat[1][1] - mat[2][2]) * 2.0f;

			qw = (mat[1][2] - mat[2][1]) / S;
			qx = 0.25f * S;
			qy = (mat[1][0] + mat[0][1]) / S;
			qz = (mat[2][0] + mat[0][2]) / S;
		}
		else if (mat[1][1] > mat[2][2])
		{
			float S = Math::Sqrt(1.0f + mat[1][1] - mat[0][0] - mat[2][2]) * 2.0f;
			qw = (mat[2][0] - mat[0][2]) / S;
			qx = (mat[1][0] + mat[0][1]) / S;
			qy = 0.25f * S;
			qz = (mat[2][1] + mat[1][2]) / S;
		}
		else
		{
			float S = Math::Sqrt(1.0f + mat[2][2] - mat[0][0] - mat[1][1]) * 2.0f;
			qw = (mat[0][1] - mat[1][0]) / S;
			qx = (mat[2][0] + mat[0][2]) / S;
			qy = (mat[2][1] + mat[1][2]) / S;
			qz = 0.25f * S;
		}

		return Quaternion(qx, qy, qz, qw);
	}

	Vector3 Matrix4x4::GetXAxis() const
	{
		return Vector3(mat[0][0], mat[0][1], mat[0][2]);
	}

	Vector3 Matrix4x4::GetYAxis() const
	{
		return Vector3(mat[1][0], mat[1][1], mat[1][2]);
	}

	Vector3 Matrix4x4::GetZAxis() const
	{
		return Vector3(mat[2][0], mat[2][1], mat[2][2]);
	}

	Matrix4x4 Matrix4x4::CreateScaleMatrix(float x, float y, float z)
	{
		float mat[4][4] =
		{
			{   x, 0.0f, 0.0f, 0.0f}, //1st column
			{0.0f,    y, 0.0f, 0.0f}, //2nd column
			{0.0f, 0.0f,    z, 0.0f}, //3rd column
			{0.0f, 0.0f, 0.0f, 1.0f}  //4th column
		};
		return Matrix4x4(mat);
	}

	Matrix4x4 Matrix4x4::CreateScaleMatrix(float size)
	{
		return CreateScaleMatrix(size, size, size);
	}

	Matrix4x4 Matrix4x4::CreateScaleMatrix(const Vector3& vec3)
	{
		return CreateScaleMatrix(vec3.x, vec3.y, vec3.z);
	}

	// theta is expected in radians
	Matrix4x4 Matrix4x4::CreateRotationXMatrix(float theta)
	{
		float mat[4][4] =
		{
			{ 1.0f,        0.0f,        0.0f, 0.0f}, //1st column
			{ 0.0f, cosf(theta), sinf(theta), 0.0f}, //2nd column
			{ 0.0f,-sinf(theta), cosf(theta), 0.0f}, //3rd column
			{ 0.0f,        0.0f,        0.0f, 1.0f}	 //4th column
		};
		return Matrix4x4(mat);
	}

	Matrix4x4 Matrix4x4::CreateRotationYMatrix(float theta)
	{
		float mat[4][4] =
		{
			{ cosf(theta), 0.0f,-sinf(theta), 0.0f}, //1st column
			{        0.0f, 1.0f,        0.0f, 0.0f}, //2nd column
			{ sinf(theta), 0.0f, cosf(theta), 0.0f}, //3rd column
			{        0.0f, 0.0f,        0.0f, 1.0f}  //4th column
		};
		return Matrix4x4(mat);
	}

	Matrix4x4 Matrix4x4::CreateRotationZMatrix(float theta)
	{
		float mat[4][4] =
		{
			{ cosf(theta), sinf(theta), 0.0f, 0.0f}, //1st column
			{-sinf(theta), cosf(theta), 0.0f, 0.0f}, //2nd column
			{        0.0f,        0.0f, 1.0f, 0.0f}, //3rd column
			{        0.0f,        0.0f, 0.0f, 1.0f}  //4th column
		};
		return Matrix4x4(mat);
	}

	Matrix4x4 Matrix4x4::CreateTranslationMatrix(float x, float y, float z)
	{
		float mat[4][4] =
		{
			{1.0f, 0.0f, 0.0f, 0.0f}, //1st column
			{0.0f, 1.0f, 0.0f, 0.0f}, //2nd column
			{0.0f, 0.0f, 1.0f, 0.0f}, //3rd column
			{   x,    y,    z, 1.0f}  //4th column
		};
		return Matrix4x4(mat);
	}

	Matrix4x4 Matrix4x4::CreateTranslationMatrix(const Vector3& vec3)
	{
		return CreateTranslationMatrix(vec3.x, vec3.y, vec3.z);
	}

	Matrix4x4 Matrix4x4::CreateLookAtMatrix(const Vector3& eye, const Vector3& target, const Vector3& worldUp)
	{
		Vector3 forward = Vector3::Normalize(target - eye);
		Vector3 left = Vector3::Normalize(Vector3::CrossProduct(worldUp, forward));
		Vector3 up = Vector3::CrossProduct(forward, left);

		// Invert matrix for world-to-object space (i.e. world-to-camera)
		float mat[4][4] =
		{
			{ left.x,   up.x, forward.x, 0.0f}, //1st column
			{ left.y,   up.y, forward.y, 0.0f}, //2nd column
			{ left.z,   up.z, forward.z, 0.0f}, //3rd column
			{  -Vector3::DotProduct(left, eye), -Vector3::DotProduct(up, eye),    -Vector3::DotProduct(forward, eye), 1.0f}  //4th column
		};
		return Matrix4x4(mat);
	}

	Matrix4x4 Matrix4x4::CreateOrthographicMatrix(float width, float height, float zNear, float zFar)
	{
		float mat[4][4] =
		{
			{ 2.0f / width,          0.0f,                             0.0f, 0.0f},
			{         0.0f, 2.0f / height,                             0.0f, 0.0f},
			{         0.0f,          0.0f,            1.0f / (zFar - zNear), 0.0f},
			{         0.0f,          0.0f,        -(zNear) / (zFar - zNear), 1.0f}
		};
		return Matrix4x4(mat);
	}

	Matrix4x4 Matrix4x4::CreatePerspectiveMatrix(float width, float height, float zNear, float zFar, float fov)
	{
		float aspect = width / height;
		float tanHalfFOV = tanf(fov / 2.0f);
		float y = 1.0f / tanf(fov / 2.0f);
		float x = y * height / width;

		float mat[4][4] =
		{
			{ 1.0f / (aspect * tanHalfFOV),              0.0f,                                      0.0f,  0.0f},
			{                         0.0f, 1.0f / tanHalfFOV,                                      0.0f,  0.0f},
			{                         0.0f,              0.0f,          -(zFar + zNear) / (zFar - zNear), -1.0f},
			{                         0.0f,              0.0f,   -(2.0f * zFar * zNear) / (zFar - zNear),  0.0f}
		};
		return Matrix4x4(mat);
	}

	//----- Define Quaternion constants ------
	const Quaternion Quaternion::Identity;
	//-------------------------------------

	Quaternion::Quaternion() :
		w(1.0f), x(0.0f), y(0.0f), z(0.0f)
	{

	}

	Quaternion::Quaternion(const Vector3& axis, float angle) :
		w(cosf(angle / 2.0f)), x(sinf(angle / 2.0f)* axis.x), y(sinf(angle / 2.0f)* axis.y), z(sinf(angle / 2.0f)* axis.z)
	{

	}

	Quaternion::Quaternion(const float& qx, const float& qy, const float& qz, const float& qw) :
		w(qw), x(qx), y(qy), z(qz)
	{

	}

	Quaternion::~Quaternion()
	{

	}

	Matrix4x4 Quaternion::ToMatrix4x4() const
	{
		float xx = x * x;
		float yy = y * y;
		float zz = z * z;
		float xy = x * y;
		float yz = y * z;
		float xz = x * z;
		float xw = x * w;
		float yw = y * w;
		float zw = z * w;

		Matrix4x4 mat4x4;
		mat4x4.mat[0][0] = 1.0f - (2.0f * yy) - (2.0f * zz);
		mat4x4.mat[1][0] = (2.0f * xy) - (2.0f * zw);
		mat4x4.mat[2][0] = (2.0f * xz) + (2.0f * yw);
		mat4x4.mat[3][0] = 0.0f;

		mat4x4.mat[0][1] = (2.0f * xy) + (2.0f * zw);
		mat4x4.mat[1][1] = 1.0f - (2.0f * xx) - (2.0f * zz);
		mat4x4.mat[2][1] = (2.0f * yz) - (2.0f * xw);
		mat4x4.mat[3][1] = 0.0f;

		mat4x4.mat[0][2] = (2.0f * xz) - (2.0f * yw);
		mat4x4.mat[1][2] = (2.0f * yz) + (2.0f * xw);
		mat4x4.mat[2][2] = 1.0f - (2.0f * xx) - (2.0f * yy);
		mat4x4.mat[3][2] = 0.0f;

		mat4x4.mat[0][3] = 0.0f;
		mat4x4.mat[1][3] = 0.0f;
		mat4x4.mat[2][3] = 0.0f;
		mat4x4.mat[3][3] = 1.0f;

		return mat4x4;
	}

	void Quaternion::Conjugate()
	{
		x *= -1.0f;
		y *= -1.0f;
		z *= -1.0f;
	}

	float Quaternion::MagnitudeSqr()
	{
		return w * w + x * x + y * y + z * z;
	}

	float Quaternion::Magnitude()
	{
		return sqrtf(MagnitudeSqr());
	}

	void Quaternion::Normalize()
	{
		float magnitude = Magnitude();
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	}

	Matrix4x4 Quaternion::CreateMatrix4x4(const Quaternion& q)
	{
		float xx = q.x * q.x;
		float yy = q.y * q.y;
		float zz = q.z * q.z;
		float xy = q.x * q.y;
		float yz = q.y * q.z;
		float xz = q.x * q.z;
		float xw = q.x * q.w;
		float yw = q.y * q.w;
		float zw = q.z * q.w;

		Matrix4x4 mat4x4;
		mat4x4.mat[0][0] = 1.0f - (2.0f * yy) - (2.0f * zz);
		mat4x4.mat[1][0] = (2.0f * xy) - (2.0f * zw);
		mat4x4.mat[2][0] = (2.0f * xz) + (2.0f * yw);
		mat4x4.mat[3][0] = 0.0f;

		mat4x4.mat[0][1] = (2.0f * xy) + (2.0f * zw);
		mat4x4.mat[1][1] = 1.0f - (2.0f * xx) - (2.0f * zz);
		mat4x4.mat[2][1] = (2.0f * yz) - (2.0f * xw);
		mat4x4.mat[3][1] = 0.0f;

		mat4x4.mat[0][2] = (2.0f * xz) - (2.0f * yw);
		mat4x4.mat[1][2] = (2.0f * yz) + (2.0f * xw);
		mat4x4.mat[2][2] = 1.0f - (2.0f * xx) - (2.0f * yy);
		mat4x4.mat[3][2] = 0.0f;

		mat4x4.mat[0][3] = 0.0f;
		mat4x4.mat[1][3] = 0.0f;
		mat4x4.mat[2][3] = 0.0f;
		mat4x4.mat[3][3] = 1.0f;

		return mat4x4;
	}

	Quaternion Quaternion::AxisAngle(const Vector3& axis, float angle)
	{
		return Quaternion(axis, angle);
	}
}