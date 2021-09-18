#pragma once

#include "Vec2.h"
#include "Vec3.h"
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

		void TestMat2(const Mat2d& check = { { 1.0f,2.5f }, { 3.0f,4.0f } }, const Mat2d& against = { { 2.0f,1.0f }, { 4.0f,3.0f } });
		void TestMat3(const Mat3d& check = { { 1.0,2.0,3.0 }, { 3.0,1.0,5.0 }, { 10.0,20.0,1.0 } },
					  const Mat3d& against = { { 2.0f,1.0f,0.0f }, { 4.0f,3.0f,2.0f }, { 40.0f,50.0f,60.0f } });
		void TestMat4(const Mat4d& check = { { 1.1,2.0,3.0,4.0 }, { 3.0,4.0,5.2,6.0 }, { 10.0,20.5,30.0,60.0 }, { 0.1,0.23,0.3,0.5 } },
					  const Mat4d& against = { { 2.0f,1.0f,0.0f,-1.0f }, { 4.0f,3.0f,2.0f,1.0f }, { 40.0f,50.0f,60.0f,70.0f }, { 0.2f,0.3f,0.4f,0.5f } });
		void AllMatrixTestCases();
	}
}