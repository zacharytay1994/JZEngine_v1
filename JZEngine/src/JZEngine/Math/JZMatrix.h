#pragma once

#include <initializer_list>
#include <assert.h>

#include "Vec2.h"

namespace JZEngine
{
	template <typename TYPE>
	struct Mat2
	{
		TYPE data_[2][2] = { {1.0,0.0},{0.0,1.0} };

		#define UNCONST_MAT2(m) const_cast<Mat2<TYPE>&>(m)

		Mat2() = default;
		Mat2(std::initializer_list<std::initializer_list<TYPE>> il)
		{
			assert(il.size() < 4);
			uint8_t cols = 0;
			for (auto& col : il)
			{
				std::copy(col.begin(), col.end(), data_[cols++]);
			}
		}
		Mat2(const Mat2& mat2)
		{
			std::memcpy(data_, mat2.data_, static_cast<size_t>(4 * sizeof(TYPE)));
		}

		Mat2& operator=(const Mat2& mat2)
		{
			std::memcpy(data_, mat2.data_, static_cast<size_t>(4 * sizeof(TYPE)));
			return *this;
		}

		Mat2& operator+=(const Mat2& rhs)
		{
			data_[0][0] += UNCONST_MAT2(rhs)[0][0];
			data_[0][1] += UNCONST_MAT2(rhs)[0][1];
			data_[1][0] += UNCONST_MAT2(rhs)[1][0];
			data_[1][1] += UNCONST_MAT2(rhs)[1][1];
			return *this;
 		}

		Mat2 operator+(const Mat2& rhs) const
		{
			Mat2 out(*this);
			out += rhs;
			return out;
		}
		
		Mat2& operator-=(const Mat2& rhs)
		{
			data_[0][0] -= UNCONST_MAT2(rhs)[0][0];
			data_[0][1] -= UNCONST_MAT2(rhs)[0][1];
			data_[1][0] -= UNCONST_MAT2(rhs)[1][0];
			data_[1][1] -= UNCONST_MAT2(rhs)[1][1];
			return *this;
		}

		Mat2 operator-(const Mat2& rhs) const
		{
			Mat2 out(*this);
			out -= rhs;
			return out;
		}

		Mat2& operator*=(const Mat2& rhs)
		{
			TYPE d00 = data_[0][0] * UNCONST_MAT2(rhs)[0][0] + data_[0][1] * UNCONST_MAT2(rhs)[1][0];
			TYPE d01 = data_[0][0] * UNCONST_MAT2(rhs)[0][1] + data_[0][1] * UNCONST_MAT2(rhs)[1][1];
			TYPE d10 = data_[1][0] * UNCONST_MAT2(rhs)[0][0] + data_[1][1] * UNCONST_MAT2(rhs)[1][0];
			TYPE d11 = data_[1][0] * UNCONST_MAT2(rhs)[0][1] + data_[1][1] * UNCONST_MAT2(rhs)[1][1];
			data_[0][0] = d00;
			data_[0][1] = d01;
			data_[1][0] = d10;
			data_[1][1] = d11;
			return *this;
		}

		template <typename VEC_TYPE>
		Vec2<TYPE> operator*(const Vec2<VEC_TYPE>& rhs) const
		{
			return { data_[0][0] * static_cast<TYPE>(rhs.x) + data_[0][1] * static_cast<TYPE>(rhs.y),
					data_[1][0] * static_cast<TYPE>(rhs.x) + data_[1][1] * static_cast<TYPE>(rhs.y) };
		}

		Mat2 operator*(const Mat2& rhs) const
		{
			Mat2 out(*this);
			out *= rhs;
			return out;
		}

		TYPE* operator[](unsigned int row)
		{
			return data_[row];
		}

		template <typename OStream>
		friend OStream& operator<<(OStream& os, const Mat2& matrix)
		{
			os << "\n:";
			for (int r = 0; r < 2; ++r)
			{
				os << "\n[ ";
				for (int c = 0; c < 2; ++c)
				{
					os << UNCONST_MAT2(matrix)[r][c] << " ";
				}
				os << "]";
			}
			os << "\n:";
			return os;
		}
	};

	template <typename TYPE>
	struct Mat3
	{
		TYPE data_[3][3] = { {1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0} };

		#define UNCONST_MAT3(m) const_cast<Mat3<TYPE>&>(m)

		Mat3() = default;
		Mat3(std::initializer_list<std::initializer_list<TYPE>> il)
		{
			assert(il.size() < 9);
			uint8_t cols = 0;
			for (auto& col : il)
			{
				std::copy(col.begin(), col.end(), data_[cols++]);
			}
		}
		Mat3(const Mat3& mat2)
		{
			std::memcpy(data_, mat2.data_, static_cast<size_t>(9 * sizeof(TYPE)));
		}

		Mat3& operator=(const Mat3& mat2)
		{
			std::memcpy(data_, mat2.data_, static_cast<size_t>(9 * sizeof(TYPE)));
			return *this;
		}

		Mat3& operator+=(const Mat3& rhs)
		{
			data_[0][0] += UNCONST_MAT3(rhs)[0][0];
			data_[0][1] += UNCONST_MAT3(rhs)[0][1];
			data_[0][2] += UNCONST_MAT3(rhs)[0][2];
			data_[1][0] += UNCONST_MAT3(rhs)[1][0];
			data_[1][1] += UNCONST_MAT3(rhs)[1][1];
			data_[1][2] += UNCONST_MAT3(rhs)[1][2];
			data_[2][0] += UNCONST_MAT3(rhs)[2][0];
			data_[2][1] += UNCONST_MAT3(rhs)[2][1];
			data_[2][2] += UNCONST_MAT3(rhs)[2][2];
			return *this;
		}

		Mat3 operator+(const Mat3& rhs) const
		{
			Mat3 out(*this);
			out += rhs;
			return out;
		}

		Mat3& operator-=(const Mat3& rhs)
		{
			data_[0][0] -= UNCONST_MAT3(rhs)[0][0];
			data_[0][1] -= UNCONST_MAT3(rhs)[0][1];
			data_[0][2] -= UNCONST_MAT3(rhs)[0][2];
			data_[1][0] -= UNCONST_MAT3(rhs)[1][0];
			data_[1][1] -= UNCONST_MAT3(rhs)[1][1];
			data_[1][2] -= UNCONST_MAT3(rhs)[1][2];
			data_[2][0] -= UNCONST_MAT3(rhs)[2][0];
			data_[2][1] -= UNCONST_MAT3(rhs)[2][1];
			data_[2][2] -= UNCONST_MAT3(rhs)[2][2];
			return *this;
		}

		Mat3 operator-(const Mat3& rhs) const
		{
			Mat3 out(*this);
			out -= rhs;
			return out;
		}

		Mat3& operator*=(const Mat3& rhs)
		{
			TYPE d00 = data_[0][0] * UNCONST_MAT3(rhs)[0][0] + data_[0][1] * UNCONST_MAT3(rhs)[1][0] + data_[0][2] * UNCONST_MAT3(rhs)[2][0];
			TYPE d01 = data_[0][0] * UNCONST_MAT3(rhs)[0][1] + data_[0][1] * UNCONST_MAT3(rhs)[1][1] + data_[0][2] * UNCONST_MAT3(rhs)[2][1];
			TYPE d02 = data_[0][0] * UNCONST_MAT3(rhs)[0][2] + data_[0][1] * UNCONST_MAT3(rhs)[1][2] + data_[0][2] * UNCONST_MAT3(rhs)[2][2];

			TYPE d10 = data_[1][0] * UNCONST_MAT3(rhs)[0][0] + data_[1][1] * UNCONST_MAT3(rhs)[1][0] + data_[1][2] * UNCONST_MAT3(rhs)[2][0];
			TYPE d11 = data_[1][0] * UNCONST_MAT3(rhs)[0][1] + data_[1][1] * UNCONST_MAT3(rhs)[1][1] + data_[1][2] * UNCONST_MAT3(rhs)[2][1];
			TYPE d12 = data_[1][0] * UNCONST_MAT3(rhs)[0][2] + data_[1][1] * UNCONST_MAT3(rhs)[1][2] + data_[1][2] * UNCONST_MAT3(rhs)[2][2];

			TYPE d20 = data_[2][0] * UNCONST_MAT3(rhs)[0][0] + data_[2][1] * UNCONST_MAT3(rhs)[1][0] + data_[2][2] * UNCONST_MAT3(rhs)[2][0];
			TYPE d21 = data_[2][0] * UNCONST_MAT3(rhs)[0][1] + data_[2][1] * UNCONST_MAT3(rhs)[1][1] + data_[2][2] * UNCONST_MAT3(rhs)[2][1];
			TYPE d22 = data_[2][0] * UNCONST_MAT3(rhs)[0][2] + data_[2][1] * UNCONST_MAT3(rhs)[1][2] + data_[2][2] * UNCONST_MAT3(rhs)[2][2];

			data_[0][0] = d00;
			data_[0][1] = d01;
			data_[0][2] = d02;

			data_[1][0] = d10;
			data_[1][1] = d11;
			data_[1][2] = d12;

			data_[2][0] = d20;
			data_[2][1] = d21;
			data_[2][2] = d22;

			return *this;
		}

		Mat3 operator*(const Mat3& rhs) const
		{
			Mat3 out(*this);
			out *= rhs;
			return out;
		}

		template <typename VEC_TYPE>
		Vec3<TYPE> operator*(const Vec3<VEC_TYPE>& rhs) const
		{
			return { data_[0][0] * static_cast<TYPE>(rhs.x) + data_[0][1] * static_cast<TYPE>(rhs.y) + +data_[0][2] * static_cast<TYPE>(rhs.z),
					data_[1][0] * static_cast<TYPE>(rhs.x) + data_[1][1] * static_cast<TYPE>(rhs.y) + data_[1][2] * static_cast<TYPE>(rhs.z),
					data_[2][0] * static_cast<TYPE>(rhs.x) + data_[2][1] * static_cast<TYPE>(rhs.y) + data_[2][2] * static_cast<TYPE>(rhs.z) };
		}

		TYPE* operator[](unsigned int row)
		{
			return data_[row];
		}

		template <typename OStream>
		friend OStream& operator<<(OStream& os, const Mat3& matrix)
		{
			os << "\n:";
			for (int r = 0; r < 3; ++r)
			{
				os << "\n[ ";
				for (int c = 0; c < 3; ++c)
				{
					os << UNCONST_MAT3(matrix)[r][c] << " ";
				}
				os << "]";
			}
			os << "\n:";
			return os;
		}
	};

	template <typename TYPE>
	struct Mat4
	{
		TYPE data_[4][4] = { { 1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0} };

		#define UNCONST_MAT4(m) const_cast<Mat4<TYPE>&>(m)

		Mat4() = default;
		Mat4(std::initializer_list<std::initializer_list<TYPE>> il)
		{
			assert(il.size() < 16);
			uint8_t cols = 0;
			for (auto& col : il)
			{
				std::copy(col.begin(), col.end(), data_[cols++]);
			}
		}
		Mat4(const Mat4& mat4)
		{
			std::memcpy(data_, mat4.data_, static_cast<size_t>(16 * sizeof(TYPE)));
		}

		Mat4& operator=(const Mat4& mat4)
		{
			std::memcpy(data_, mat4.data_, static_cast<size_t>(16 * sizeof(TYPE)));
			return *this;
		}

		Mat4& operator+=(const Mat4& rhs)
		{
			data_[0][0] += UNCONST_MAT4(rhs)[0][0];
			data_[0][1] += UNCONST_MAT4(rhs)[0][1];
			data_[0][2] += UNCONST_MAT4(rhs)[0][2];
			data_[0][3] += UNCONST_MAT4(rhs)[0][3];

			data_[1][0] += UNCONST_MAT4(rhs)[1][0];
			data_[1][1] += UNCONST_MAT4(rhs)[1][1];
			data_[1][2] += UNCONST_MAT4(rhs)[1][2];
			data_[1][3] += UNCONST_MAT4(rhs)[1][3];

			data_[2][0] += UNCONST_MAT4(rhs)[2][0];
			data_[2][1] += UNCONST_MAT4(rhs)[2][1];
			data_[2][2] += UNCONST_MAT4(rhs)[2][2];
			data_[2][3] += UNCONST_MAT4(rhs)[2][3];

			data_[3][0] += UNCONST_MAT4(rhs)[3][0];
			data_[3][1] += UNCONST_MAT4(rhs)[3][1];
			data_[3][2] += UNCONST_MAT4(rhs)[3][2];
			data_[3][3] += UNCONST_MAT4(rhs)[3][3];

			return *this;
		}

		Mat4 operator+(const Mat4& rhs) const
		{
			Mat4 out(*this);
			out += rhs;
			return out;
		}

		Mat4& operator-=(const Mat4& rhs)
		{
			data_[0][0] -= UNCONST_MAT4(rhs)[0][0];
			data_[0][1] -= UNCONST_MAT4(rhs)[0][1];
			data_[0][2] -= UNCONST_MAT4(rhs)[0][2];
			data_[0][3] -= UNCONST_MAT4(rhs)[0][3];

			data_[1][0] -= UNCONST_MAT4(rhs)[1][0];
			data_[1][1] -= UNCONST_MAT4(rhs)[1][1];
			data_[1][2] -= UNCONST_MAT4(rhs)[1][2];
			data_[1][3] -= UNCONST_MAT4(rhs)[1][3];

			data_[2][0] -= UNCONST_MAT4(rhs)[2][0];
			data_[2][1] -= UNCONST_MAT4(rhs)[2][1];
			data_[2][2] -= UNCONST_MAT4(rhs)[2][2];
			data_[2][3] -= UNCONST_MAT4(rhs)[2][3];

			data_[3][0] -= UNCONST_MAT4(rhs)[3][0];
			data_[3][1] -= UNCONST_MAT4(rhs)[3][1];
			data_[3][2] -= UNCONST_MAT4(rhs)[3][2];
			data_[3][3] -= UNCONST_MAT4(rhs)[3][3];

			return *this;
		}

		Mat4 operator-(const Mat4& rhs) const
		{
			Mat4 out(*this);
			out -= rhs;
			return out;
		}

		Mat4& operator*=(const Mat4& rhs)
		{
			TYPE d00 = data_[0][0] * UNCONST_MAT4(rhs)[0][0] + data_[0][1] * UNCONST_MAT4(rhs)[1][0] + data_[0][2] * UNCONST_MAT4(rhs)[2][0] + data_[0][3] * UNCONST_MAT4(rhs)[3][0];
			TYPE d01 = data_[0][0] * UNCONST_MAT4(rhs)[0][1] + data_[0][1] * UNCONST_MAT4(rhs)[1][1] + data_[0][2] * UNCONST_MAT4(rhs)[2][1] + data_[0][3] * UNCONST_MAT4(rhs)[3][1];
			TYPE d02 = data_[0][0] * UNCONST_MAT4(rhs)[0][2] + data_[0][1] * UNCONST_MAT4(rhs)[1][2] + data_[0][2] * UNCONST_MAT4(rhs)[2][2] + data_[0][3] * UNCONST_MAT4(rhs)[3][2];
			TYPE d03 = data_[0][0] * UNCONST_MAT4(rhs)[0][3] + data_[0][1] * UNCONST_MAT4(rhs)[1][3] + data_[0][2] * UNCONST_MAT4(rhs)[2][3] + data_[0][3] * UNCONST_MAT4(rhs)[3][3];

			TYPE d10 = data_[1][0] * UNCONST_MAT4(rhs)[0][0] + data_[1][1] * UNCONST_MAT4(rhs)[1][0] + data_[1][2] * UNCONST_MAT4(rhs)[2][0] + data_[1][3] * UNCONST_MAT4(rhs)[3][0];
			TYPE d11 = data_[1][0] * UNCONST_MAT4(rhs)[0][1] + data_[1][1] * UNCONST_MAT4(rhs)[1][1] + data_[1][2] * UNCONST_MAT4(rhs)[2][1] + data_[1][3] * UNCONST_MAT4(rhs)[3][1];
			TYPE d12 = data_[1][0] * UNCONST_MAT4(rhs)[0][2] + data_[1][1] * UNCONST_MAT4(rhs)[1][2] + data_[1][2] * UNCONST_MAT4(rhs)[2][2] + data_[1][3] * UNCONST_MAT4(rhs)[3][2];
			TYPE d13 = data_[1][0] * UNCONST_MAT4(rhs)[0][3] + data_[1][1] * UNCONST_MAT4(rhs)[1][3] + data_[1][2] * UNCONST_MAT4(rhs)[2][3] + data_[1][3] * UNCONST_MAT4(rhs)[3][3];

			TYPE d20 = data_[2][0] * UNCONST_MAT4(rhs)[0][0] + data_[2][1] * UNCONST_MAT4(rhs)[1][0] + data_[2][2] * UNCONST_MAT4(rhs)[2][0] + data_[2][3] * UNCONST_MAT4(rhs)[3][0];
			TYPE d21 = data_[2][0] * UNCONST_MAT4(rhs)[0][1] + data_[2][1] * UNCONST_MAT4(rhs)[1][1] + data_[2][2] * UNCONST_MAT4(rhs)[2][1] + data_[2][3] * UNCONST_MAT4(rhs)[3][1];
			TYPE d22 = data_[2][0] * UNCONST_MAT4(rhs)[0][2] + data_[2][1] * UNCONST_MAT4(rhs)[1][2] + data_[2][2] * UNCONST_MAT4(rhs)[2][2] + data_[2][3] * UNCONST_MAT4(rhs)[3][2];
			TYPE d23 = data_[2][0] * UNCONST_MAT4(rhs)[0][3] + data_[2][1] * UNCONST_MAT4(rhs)[1][3] + data_[2][2] * UNCONST_MAT4(rhs)[2][3] + data_[2][3] * UNCONST_MAT4(rhs)[3][3];

			TYPE d30 = data_[3][0] * UNCONST_MAT4(rhs)[0][0] + data_[3][1] * UNCONST_MAT4(rhs)[1][0] + data_[3][2] * UNCONST_MAT4(rhs)[2][0] + data_[3][3] * UNCONST_MAT4(rhs)[3][0];
			TYPE d31 = data_[3][0] * UNCONST_MAT4(rhs)[0][1] + data_[3][1] * UNCONST_MAT4(rhs)[1][1] + data_[3][2] * UNCONST_MAT4(rhs)[2][1] + data_[3][3] * UNCONST_MAT4(rhs)[3][1];
			TYPE d32 = data_[3][0] * UNCONST_MAT4(rhs)[0][2] + data_[3][1] * UNCONST_MAT4(rhs)[1][2] + data_[3][2] * UNCONST_MAT4(rhs)[2][2] + data_[3][3] * UNCONST_MAT4(rhs)[3][2];
			TYPE d33 = data_[3][0] * UNCONST_MAT4(rhs)[0][3] + data_[3][1] * UNCONST_MAT4(rhs)[1][3] + data_[3][2] * UNCONST_MAT4(rhs)[2][3] + data_[3][3] * UNCONST_MAT4(rhs)[3][3];

			data_[0][0] = d00;
			data_[0][1] = d01;
			data_[0][2] = d02;
			data_[0][3] = d03;

			data_[1][0] = d10;
			data_[1][1] = d11;
			data_[1][2] = d12;
			data_[1][3] = d13;

			data_[2][0] = d20;
			data_[2][1] = d21;
			data_[2][2] = d22;
			data_[2][3] = d23;

			data_[3][0] = d30;
			data_[3][1] = d31;
			data_[3][2] = d32;
			data_[3][3] = d33;

			return *this;
		}

		Mat4 operator*(const Mat4& rhs) const
		{
			Mat4 out(*this);
			out *= rhs;
			return out;
		}

		/*template <typename VEC_TYPE>
		Vec3<TYPE> operator*(const Vec3<VEC_TYPE>& rhs) const
		{
			return { data_[0][0] * static_cast<TYPE>(rhs.x) + data_[0][1] * static_cast<TYPE>(rhs.y) + +data_[0][2] * static_cast<TYPE>(rhs.z),
					data_[1][0] * static_cast<TYPE>(rhs.x) + data_[1][1] * static_cast<TYPE>(rhs.y) + data_[1][2] * static_cast<TYPE>(rhs.z),
					data_[2][0] * static_cast<TYPE>(rhs.x) + data_[2][1] * static_cast<TYPE>(rhs.y) + data_[2][2] * static_cast<TYPE>(rhs.z) };
		}*/

		TYPE* operator[](unsigned int row)
		{
			return data_[row];
		}

		template <typename OStream>
		friend OStream& operator<<(OStream& os, const Mat4& matrix)
		{
			os << "\n:";
			for (int r = 0; r < 4; ++r)
			{
				os << "\n[ ";
				for (int c = 0; c < 4; ++c)
				{
					os << UNCONST_MAT4(matrix)[r][c] << " ";
				}
				os << "]";
			}
			os << "\n:";
			return os;
		}
	};

	typedef Mat2<double> Mat2d;
	typedef Mat3<double> Mat3d;
	typedef Mat4<double> Mat4d;

	namespace Math
	{
		void Mat2TestCases()
		{
			Mat2<float> mat2_0{ { 1.0f,2.5f }, { 3.0f,4.0f } };
			Mat2<float> mat2_1{ { 2.0f,1.0f }, { 4.0f,3.0f } };
			Mat2d mat2_2;
			Vec2<int> vec2{ 3,2 };
			Log::Info("Math", "Mat2 Identity: {}", mat2_2);
			//Log::Info("Math", "Mat2 Print: {}", mat2_0);
			//Log::Info("Math", "Mat2 +=: {}", mat2_0 += mat2_1);
			//Log::Info("Math", "Mat2 +: {}", mat2_0 + mat2_1);
			/*Log::Info("Math", "Mat2 -=: {}", mat2_0 -= mat2_1);
			Log::Info("Math", "Mat2 -: {}", mat2_0 - mat2_1);*/
			/*Log::Info("Math", "Mat2 *=: {}", mat2_0 *= mat2_1);
			Log::Info("Math", "Mat2 * Vec2: {}", mat2_0 * mat2_1);*/
		}
		void Mat3TestCases()
		{
			Mat3<float> mat3_0{ { 1.0f,2.0f,3.0f }, { 3.0f,4.0f,5.0f }, { 10.0f,20.0f,30.0f } };
			Mat3<float> mat3_1{ { 2.0f,1.0f,0.0f }, { 4.0f,3.0f,2.0f }, { 40.0f,50.0f,60.0f } };
			Mat3d mat3_2;
			Vec3<int> vec3{ 3,2,1 };
			Log::Info("Math", "Mat3 Identity: {}", mat3_2);
			Log::Info("Math", "Mat3 Print: {}", mat3_0);
			Log::Info("Math", "Mat3 * Vec3: {}", mat3_0 * vec3);
		}

		void Mat4TestCases()
		{
			Mat4<float> mat4_0{ { 1.0f,2.0f,3.0f,4.0f }, { 3.0f,4.0f,5.0f,6.0f }, { 10.0f,20.0f,30.0f,40.0f }, { 0.1f,0.2f,0.3f,0.4f } };
			Mat4<float> mat4_1{ { 2.0f,1.0f,0.0f,-1.0f }, { 4.0f,3.0f,2.0f,1.0f }, { 40.0f,50.0f,60.0f,70.0f }, { 0.2f,0.3f,0.4f,0.5f } };
			Mat4d mat4_2;
			Log::Info("Math", "Mat4 Identity: {}", mat4_2);
			Log::Info("Math", "Mat4 Print: {}", mat4_0);
			Log::Info("Math", "Mat4 + Mat4: {}", mat4_0 + mat4_1);
			Log::Info("Math", "Mat4 * Mat4: {}", mat4_0 * mat4_1 * mat4_0);
		}

		void AllMatrixTestCases()
		{
			Mat2TestCases();
			Mat3TestCases();
			Mat4TestCases();
		}
	}

	//template <typename TYPE, size_t ROW, size_t COLUMN>
	//struct Matrix
	//{
	//	const TYPE rows_, cols_;

	//	TYPE data_[ROW][COLUMN]{ 0 };

	//	Matrix()
	//		:
	//		rows_(ROW),
	//		cols_(COLUMN)
	//	{}

	//	Matrix(std::initializer_list<std::initializer_list<TYPE>> il)
	//		:
	//		rows_(ROW),
	//		cols_(COLUMN)
	//	{
	//		//assert(il.size() < ROW);
	//		uint8_t cols = 0;
	//		for (auto& col : il)
	//		{
	//			//assert(col.size() < COLUMN);
	//			std::copy(col.begin(), col.end(), data_[cols++]);
	//		}
	//	}

	//	Matrix& operator=(const Matrix& rhs)
	//	{
	//		std::memcpy(data_, rhs.data_, static_cast<size_t>(rows_ * cols_ * sizeof(TYPE)));
	//		return *this;
	//	}

	//	TYPE* operator[](unsigned int row)
	//	{
	//		return data_[row];
	//	}

	//	Matrix operator+(const Matrix& rhs) const
	//	{
	//		Matrix out;
	//		for (int r = 0; r < ROW; ++r)
	//		{
	//			for (int c = 0; c < COLUMN; ++c)
	//			{
	//				out[r][c] = (*const_cast<Matrix*>(this))[r][c] + const_cast<Matrix&>(rhs)[r][c];
	//			}
	//		}
	//		return out;
	//	}

	//	Matrix& operator+=(const Matrix& rhs)
	//	{
	//		*this = *this + rhs;
	//		return *this;
	//	}

	//	Matrix operator-(const Matrix& rhs) const
	//	{
	//		Matrix out;
	//		for (int r = 0; r < ROW; ++r)
	//		{
	//			for (int c = 0; c < COLUMN; ++c)
	//			{
	//				out[r][c] = (*const_cast<Matrix*>(this))[r][c] - const_cast<Matrix&>(rhs)[r][c];
	//			}
	//		}
	//		return out;
	//	}

	//	Matrix& operator-=(const Matrix& rhs)
	//	{
	//		*this = *this - rhs;
	//		return *this;
	//	}

	//	template <typename OStream>
	//	friend OStream& operator<<(OStream& os, const Matrix& matrix)
	//	{
	//		os << "\n";
	//		for (int r = 0; r < ROW; ++r)
	//		{
	//			os << "| ";
	//			for (int c = 0; c < COLUMN; ++c)
	//			{
	//				os << const_cast<Matrix&>(matrix)[r][c] << " ";
	//			}
	//			os << "|\n";
	//		}
	//		return os;
	//	}
	//};

	//template <typename MATRIX>
	//void MatrixTestCases(MATRIX& matrix, MATRIX& matrix2)
	//{
	//	Log::Info("Math", "Printing out matrix values: {}", matrix);
	//	
	//	for (int r = 0; r < matrix.rows_; ++r)
	//	{
	//		for (int c = 0; c < matrix.cols_; ++c)
	//		{
	//			Log::Info("Math", "Matrix[{}][{}] = {}", r, c, matrix[r][c]);
	//		}
	//	}

	//	Log::Info("Math", "Matrix Addition: {}", matrix + matrix2);

	//	MATRIX inner_test;
	//	Log::Info("Math", "Matrix Addition=: {} ", inner_test += matrix2);

	//	Log::Info("Math", "Matrix Subtraction=: {} ", inner_test -= matrix2);
	//}
}