#pragma once
#include <math.h>
#include <cmath>
#include <algorithm>
#define M_RADPI		57.295779513082
#define PI			3.14159265358979323846
#define DEG2RAD(x)	((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x)	((float)(x) * (float)(180.0f / (float)(PI)))
#define SQUARE(x)	(x * x)

#undef min
#undef max

#pragma warning(disable : 4244)

struct Vec3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vec3(void)
	{
		x = y = z = 0.0f;
	}

	Vec3(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	Vec3(float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vec3(const float* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vec3(const Vec3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	Vec3& operator=(const Vec3& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	Vec3& operator+=(const Vec3& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	Vec3& operator-=(const Vec3& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	Vec3& operator*=(const Vec3& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	Vec3& operator/=(const Vec3& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	Vec3& operator+=(float v)
	{
		x += v; y += v; z += v; return *this;
	}

	Vec3& operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	Vec3& operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	Vec3& operator/=(float v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	Vec3 operator+(const Vec3& v) const
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3 operator-(const Vec3& v) const
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	Vec3 operator*(const Vec3& v) const
	{
		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	Vec3 operator/(const Vec3& v) const
	{
		return Vec3(x / v.x, y / v.y, z / v.z);
	}

	Vec3 operator+(float v) const
	{
		return Vec3(x + v, y + v, z + v);
	}

	Vec3 operator-(float v) const
	{
		return Vec3(x - v, y - v, z - v);
	}

	Vec3 operator*(float v) const
	{
		return Vec3(x * v, y * v, z * v);
	}

	Vec3 operator/(float v) const
	{
		return Vec3(x / v, y / v, z / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}

	float Length(void) const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float Size(void) const
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	float Length2d(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float Length2dSqr(void) const
	{
		return (x * x + y * y);
	}

	void NormalizeInPlace()
	{
		Vec3& v = *this;

		float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;
	}

	float DistTo(const Vec3& v) const
	{
		return (*this - v).Length();
	}

	float DistToSqr(const Vec3& v) const
	{
		return (*this - v).LengthSqr();
	}

	float Dot(const Vec3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	Vec3 Cross(const Vec3& v) const
	{
		return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f
			&& y > -0.01f && y < 0.01f
			&& z > -0.01f && z < 0.01f);
	}
};

typedef float matrix3x4[3][4];

namespace Math
{
	inline double __declspec (naked) __fastcall fsqrt(double n)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}

	inline void VectorAngles(Vec3 &vForward, Vec3 &vAngles)
	{
		float tmp, yaw, pitch;

		if (vForward.y == 0.0f && vForward.x == 0.0f)
		{
			yaw = 0.0f;

			if (vForward.z > 0.0f)
				pitch = 270.0f;
			else
				pitch = 90.0f;
		}

		else
		{
			yaw = RAD2DEG(atan2f(vForward.y, vForward.x));

			if (yaw < 0.0f)
				yaw += 360.0f;

			tmp = vForward.Length2d();
			pitch = RAD2DEG(atan2f(-vForward.z, tmp));

			if (pitch < 0.0f)
				pitch += 360.0f;
		}

		vAngles.x = pitch;
		vAngles.y = yaw;
		vAngles.z = 0.0f;
	}

	inline void MakeVector(Vec3 vAngle, Vec3 &vVector)
	{
		float fPitch = float(vAngle.x * PI / 180.0f);
		float fYaw = float(vAngle.y * PI / 180.0f);
		float fTmp = float(cos(fPitch));

		vVector.x = (-fTmp * -cosf(fYaw));
		vVector.y = (sinf(fYaw) * fTmp);
		vVector.z = -sinf(fPitch);
	}

	inline void AngleVectors(const Vec3 &angles, Vec3 *forward)
	{
		float sp, sy, cp, cy;

		sy = sinf(DEG2RAD(angles.y));
		cy = cosf(DEG2RAD(angles.y));

		sp = sinf(DEG2RAD(angles.x));
		cp = cosf(DEG2RAD(angles.x));

		forward->x = (cp * cy);
		forward->y = (cp * sy);
		forward->z = -sp;
	}

	inline float DotProduct(const float *v1, const float *v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	inline void SinCos(float radians, float *sine, float *cosine)
	{
		_asm
		{
			fld		DWORD PTR[radians]
			fsincos

			mov edx, DWORD PTR[cosine]
			mov eax, DWORD PTR[sine]

			fstp DWORD PTR[edx]
			fstp DWORD PTR[eax]
		}
	}

	inline void VectorTransform(const Vec3 &vSome, const matrix3x4 &vMatrix, Vec3 &vOut)
	{
		for (auto i = 0; i < 3; i++)
			vOut[i] = vSome.Dot((Vec3 &)vMatrix[i]) + vMatrix[i][3];
	}

	inline void MatrixSetColumn(const Vec3 &in, int column, matrix3x4 &out)
	{
		out[0][column] = in.x;
		out[1][column] = in.y;
		out[2][column] = in.z;
	}

	inline void MatrixCopy(const matrix3x4 &source, matrix3x4 &target)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				target[i][j] = source[i][j];
			}
		}
	}

	inline void AngleMatrix(const Vec3 &angles, matrix3x4 &matrix)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		// matrix = (YAW * PITCH) * ROLL
		matrix[0][0] = cp * cy;
		matrix[1][0] = cp * sy;
		matrix[2][0] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;
		matrix[0][1] = sp * srcy - crsy;
		matrix[1][1] = sp * srsy + crcy;
		matrix[2][1] = sr * cp;

		matrix[0][2] = sp * crcy + srsy;
		matrix[1][2] = sp * crsy - srcy;
		matrix[2][2] = cr * cp;

		matrix[0][3] = 0.0f;
		matrix[1][3] = 0.0f;
		matrix[2][3] = 0.0f;
	}

	inline void AngleMatrix(const Vec3 &angles, const Vec3 &origin, matrix3x4 &matrix)
	{
		AngleMatrix(angles, matrix);
		MatrixSetColumn(origin, 3, matrix);
	}

	inline void ConcatTransforms(const matrix3x4 &in1, const matrix3x4 &in2, matrix3x4 &out)
	{
		if (&in1 == &out) {
			matrix3x4 in1b;
			MatrixCopy(in1, in1b);
			ConcatTransforms(in1b, in2, out);
			return;
		}

		if (&in2 == &out) {
			matrix3x4 in2b;
			MatrixCopy(in2, in2b);
			ConcatTransforms(in1, in2b, out);
			return;
		}

		out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
			in1[0][2] * in2[2][0];
		out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
			in1[0][2] * in2[2][1];
		out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
			in1[0][2] * in2[2][2];
		out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
			in1[0][2] * in2[2][3] + in1[0][3];
		out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
			in1[1][2] * in2[2][0];
		out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
			in1[1][2] * in2[2][1];
		out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
			in1[1][2] * in2[2][2];
		out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
			in1[1][2] * in2[2][3] + in1[1][3];
		out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
			in1[2][2] * in2[2][0];
		out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
			in1[2][2] * in2[2][1];
		out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
			in1[2][2] * in2[2][2];
		out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
			in1[2][2] * in2[2][3] + in1[2][3];
	}

	inline void MatrixMultiply(const matrix3x4 &in1, const matrix3x4 &in2, matrix3x4 &out)
	{
		ConcatTransforms(in1, in2, out);
	}

	inline void VectorRotate(const float *in1, const matrix3x4 &in2, float *out)
	{
		out[0] = DotProduct(in1, in2[0]);
		out[1] = DotProduct(in1, in2[1]);
		out[2] = DotProduct(in1, in2[2]);
	}

	inline void VectorRotate(const Vec3 &in1, const matrix3x4 &in2, Vec3 &out)
	{
		VectorRotate(&in1.x, in2, &out.x);
	}

	inline void VectorRotate(const Vec3 &in1, const Vec3 &in2, Vec3 &out)
	{
		matrix3x4 matRotate;
		AngleMatrix(in2, matRotate);
		VectorRotate(in1, matRotate, out);
	}

	inline float NormalizeAngle(float ang)
	{
		if (!std::isfinite(ang))
			return 0.0f;

		return std::remainder(ang, 360.0f);
	}

	inline void ClampAngles(Vec3 &v)
	{
		v.x = std::max(-89.0f, std::min(89.0f, NormalizeAngle(v.x)));
		v.y = NormalizeAngle(v.y);
		v.z = 0.0f;
	}

	inline Vec3 CalcAngle(const Vec3 &src, const Vec3 &dst)
	{
		Vec3 ang = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 delta = (src - dst);
		float fHyp = fsqrt((delta.x * delta.x) + (delta.y * delta.y));

		ang.x = (atanf(delta.z / fHyp) * M_RADPI);
		ang.y = (atanf(delta.y / delta.x) * M_RADPI);
		ang.z = 0.0f;

		if (delta.x >= 0.0f)
			ang.y += 180.0f;

		return ang;
	}

	inline float CalcFov(const Vec3 &src, const Vec3 &dst)
	{
		Vec3 v_src = Vec3();
		AngleVectors(src, &v_src);

		Vec3 v_dst = Vec3();
		AngleVectors(dst, &v_dst);

		float result = RAD2DEG(acos(v_dst.Dot(v_src) / v_dst.LengthSqr()));

		if (!isfinite(result) || isinf(result) || isnan(result))
			result = 0.0f;

		return result;
	}

	inline float LerpFloat(float v0, float v1, float t) {
		return (1 - t) * v0 + t * v1;
	}

	inline float MapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	inline float SineEaseIn(float p) {
		return sin((p - 1) * (PI / 2.0f)) + 1;
	}

	inline float CircularEaseOut(float p) {
		return sqrt((2 - p) * p);
	}

	inline float ExponentialEaseOut(float p) {
		return (p == 1.0f) ? p : 1 - pow(2, -10 * p);
	}

	inline float BounceEaseOut(float p) {
		if (p < 4 / 11.0f)
			return (121 * p * p) / 16.0f;

		else if (p < 8 / 11.0f)
			return (363 / 40.0f * p * p) - (99 / 10.0f * p) + 17 / 5.0f;

		else if (p < 9 / 10.0f)
			return (4356 / 361.0f * p * p) - (35442 / 1805.0f * p) + 16061 / 1805.0f;

		else return (54 / 5.0f * p * p) - (513 / 25.0f * p) + 268 / 25.0f;
	}

	inline float BounceEaseIn(float p) {
		return 1 - BounceEaseOut(1 - p);
	}

	inline float BounceEaseInOut(float p) {
		return (p < 0.5f ? 0.5f * BounceEaseIn(p * 2) : 0.5f * BounceEaseOut(p * 2 - 1) + 0.5f);
	}
}