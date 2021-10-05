#pragma once

#include <limits>
#include <cmath>
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "JZMatrix.h"

namespace JZEngine
{
	namespace Math
	{	
		constexpr float PI = 3.1415926535897932384626433832795f;
		constexpr float PIx2 = 3.1415926535897932384626433832795f * 2.0f;

		template <typename T>
		T RadToDeg(T val)
		{
			return static_cast<T>(val * (180.0 / PI));
		}

		template <typename T>
		T DegToRad(T val)
		{
			return static_cast<T>(val * (PI / 180.0));
		}

		template <typename T>
		float	Get2DVectorDistance(const Vec2<T>& vec0, const Vec2<T>& vec1)
		{
			return sqrtf((vec0.x - vec1.x) * (vec0.x - vec1.x) + (vec0.y - vec1.y) * (vec0.y - vec1.y));
		}

		template <typename T>
		Vec2<T> GetRotatedVector(const Vec2<T>& vec, double radian)
		{
			return Mat2<T>::Rotate(radian) * vec;
		}

		template <typename T>
		Vec2<T>& RotateVector(Vec2<T>& vec, double radian)
		{
			return vec = GetRotatedVector(vec, radian);
		}

		template <typename T>
		Vec3<T> GetRotatedVectorX(const Vec3<T>& vec, double radian)
		{
			return Mat3<T>::RotateX(radian) * vec;
		}

		template <typename T>
		Vec3<T>& RotateVectorX(Vec3<T>& vec, double radian)
		{
			return vec = GetRotatedVectorX(vec, radian);
		}

		template <typename T>
		Vec3<T> GetRotatedVectorY(const Vec3<T>& vec, double radian)
		{
			return Mat3<T>::RotateY(radian) * vec;
		}

		template <typename T>
		Vec3<T>& RotateVectorY(Vec3<T>& vec, double radian)
		{
			return vec = GetRotatedVectorY(vec, radian);
		}

		template <typename T>
		Vec3<T> GetRotatedVectorZ(const Vec3<T>& vec, double radian)
		{
			return Mat3<T>::RotateZ(radian) * vec;
		}

		template <typename T>
		Vec3<T>& RotateVectorZ(Vec3<T>& vec, double radian)
		{
			return vec = GetRotatedVectorZ(vec, radian);
		}

		Mat3f GetModelTransformNonTransposed(const Vec2f& position, float rotate, const Vec2f& scale, const Vec2f& size);

		Mat3f GetProjectionTransformNonTransposed();

		Mat3f GetTransform( const Vec2f& position, float rotate, const Vec2f& scale, const Vec2f& size );

		//template<class T>
		//typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
		//	AlmostEqual(T a, T b, int precision)
		//{
		//	return std::fabs(a - b) <= std::numeric_limits<T>::epsilon() * std::fabs(a + b) * precision
		//		// unless the result is subnormal
		//		|| std::fabs(a - b) < std::numeric_limits<T>::min();
		//}

		bool IsEven(int val);

		void TestMat2(const Mat2d& check = { { 1.0f,2.5f }, { 3.0f,4.0f } }, const Mat2d& against = { { 2.0f,1.0f }, { 4.0f,3.0f } });

		void TestMat3(const Mat3d& check = { { 1.0,2.0,3.0 }, { 3.0,1.0,5.0 }, { 10.0,20.0,1.0 } },
					  const Mat3d& against = { { 2.0f,1.0f,0.0f }, { 4.0f,3.0f,2.0f }, { 40.0f,50.0f,60.0f } });

		void TestMat4(const Mat4d& check = { { 1.1,2.0,3.0,4.0 }, { 3.0,4.0,5.2,6.0 }, { 10.0,20.5,30.0,60.0 }, { 0.1,0.23,0.3,0.5 } },
					  const Mat4d& against = { { 2.0f,1.0f,0.0f,-1.0f }, { 4.0f,3.0f,2.0f,1.0f }, { 40.0f,50.0f,60.0f,70.0f }, { 0.2f,0.3f,0.4f,0.5f } });

		void AllMatrixTestCases();
	}
}