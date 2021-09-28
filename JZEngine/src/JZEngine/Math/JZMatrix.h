#pragma once

#include <initializer_list>
#include <assert.h>
#include <iomanip>
#include "../DebugTools/Log.h"

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "../DebugTools/Log.h"

namespace JZEngine
{
	template <typename TYPE> struct Mat3;
	template <typename TYPE> struct Mat4;
	template <typename TYPE>
	struct Mat2
	{
		TYPE data_[2][2] = { {0,0},{0,0} };

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
		template <typename INCOMING_TYPE>
		Mat2(const Mat2<INCOMING_TYPE>& mat2)
		{
			data_[0][0] = static_cast<TYPE>(mat2.data_[0][0]);
			data_[0][1] = static_cast<TYPE>(mat2.data_[0][1]);
			data_[1][0] = static_cast<TYPE>(mat2.data_[1][0]);
			data_[1][1] = static_cast<TYPE>(mat2.data_[1][1]);
		}

		static Mat2 Identity()
		{
			return { {1,0},{0,1} };
		}

		static Mat2 Scale(TYPE x, TYPE y)
		{
			return { {x, 0},
					 {0, y} };
		}

		static Mat2 Rotate(double radian)
		{
			return { {static_cast<TYPE>(std::cos(radian)), static_cast<TYPE>(-std::sin(radian))},
					 {static_cast<TYPE>(std::sin(radian)), static_cast<TYPE>(std::cos(radian))} };
		}

		explicit operator Mat3<TYPE>() const
		{
			return { {data_[0][0],data_[0][1],0}, {data_[1][0],data_[1][1],0}, {0,0,1} };
		}

		explicit operator Mat4<TYPE>() const
		{
			return { {data_[0][0],data_[0][1],0,0}, {data_[1][0],data_[1][1],0,0}, {0,0,1,0}, {0,0,0,1} };
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

		Mat2& operator*=(const double& val)
		{
			data_[0][0] *= val;
			data_[0][1] *= val;
			data_[1][0] *= val;
			data_[1][1] *= val;
			return *this;
		}

		Mat2 operator*(const double& val)
		{
			Mat2 out(*this);
			out *= val;
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
					os << std::setw(10) << std::fixed << std::setprecision(5) << UNCONST_MAT2(matrix)[r][c] << ", ";
				}
				os << "]";
			}
			os << "\n:";
			return os;
		}

		TYPE Determinant() const
		{
			return data_[0][0] * data_[1][1] - data_[1][0] * data_[0][1];
		}

		Mat2 GetTranspose() const
		{
			return { {data_[0][0], data_[1][0]},
					 {data_[0][1], data_[1][1]} };
		}

		Mat2& Transpose()
		{
			return (*this = GetTranspose());
		}

		Mat2 GetInverse() const
		{
			// check if determinant != 0
			TYPE determinant = Determinant();
			if (determinant != 0)
			{
				Mat2 temp{ {data_[1][1], -data_[0][1]}, {-data_[1][0], data_[0][0]} };
				return temp * (1.0 / determinant);
			}
			return Identity();
		}

		Mat2& Inverse()
		{
			return (*this = GetInverse());
		}
	};

	template <typename TYPE>
	struct Mat3
	{
		TYPE data_[3][3] = { {1,0,0}, {0,1,0}, {0,0,1} };

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
		Mat3(const Mat3& mat3)
		{
			std::memcpy(data_, mat3.data_, static_cast<size_t>(9 * sizeof(TYPE)));
		}
		template <typename INCOMING_TYPE>
		Mat3(const Mat3<INCOMING_TYPE>& mat3)
		{
			data_[0][0] = static_cast<TYPE>(mat3.data_[0][0]);
			data_[0][1] = static_cast<TYPE>(mat3.data_[0][1]);
			data_[0][2] = static_cast<TYPE>(mat3.data_[0][2]);
			data_[1][0] = static_cast<TYPE>(mat3.data_[1][0]);
			data_[1][1] = static_cast<TYPE>(mat3.data_[1][1]);
			data_[1][2] = static_cast<TYPE>(mat3.data_[1][2]);
			data_[2][0] = static_cast<TYPE>(mat3.data_[2][0]);
			data_[2][1] = static_cast<TYPE>(mat3.data_[2][1]);
			data_[2][2] = static_cast<TYPE>(mat3.data_[2][2]);
		}

		static Mat3 Identity()
		{
			return { {1.0,0.0,0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0} };
		}

		static Mat3 Scale(TYPE x, TYPE y, TYPE z)
		{
			return { {x,0,0},
					 {0,y,0},
					 {0,0,z} };
		}

		static Mat3 RotateZ(double radian)
		{
			return { {static_cast<TYPE>(std::cos(radian)), static_cast<TYPE>(-std::sin(radian)), 0},
					 {static_cast<TYPE>(std::sin(radian)), static_cast<TYPE>(std::cos(radian)), 0},
					 {0,0,1} };
		}

		static Mat3 RotateX(double radian)
		{
			return { {1,0,0},
					 {0, static_cast<TYPE>(std::cos(radian)), static_cast<TYPE>(-std::sin(radian))},
					 {0, static_cast<TYPE>(std::sin(radian)), static_cast<TYPE>(std::cos(radian))} };
		}

		static Mat3 RotateY(double radian)
		{
			return { {static_cast<TYPE>(std::cos(radian)), 0, static_cast<TYPE>(std::sin(radian))},
					 {0, 1, 0},
					 {static_cast<TYPE>(-std::sin(radian)), 0, static_cast<TYPE>(std::cos(radian))} };
		}

		static Mat3 Translate(TYPE x, TYPE y)
		{
			return { {1,0,x},
					 {0,1,y},
					 {0,0,1} };
		}

		explicit operator Mat2<TYPE>() const
		{
			return { {data_[0][0],data_[0][1]}, {data_[1][0],data_[1][1]} };
		}

		explicit operator Mat4<TYPE>() const
		{
			return { {data_[0][0],data_[0][1],data_[0][2],0}, {data_[1][0],data_[1][1],data_[1][2],0}, {data_[2][0],data_[2][1],data_[2][2],0}, {0,0,0,1} };
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

		Mat3& operator*=(const double val)
		{
			data_[0][0] *= val;
			data_[0][1] *= val;
			data_[0][2] *= val;
			data_[1][0] *= val;
			data_[1][1] *= val;
			data_[1][2] *= val;
			data_[2][0] *= val;
			data_[2][1] *= val;
			data_[2][2] *= val;
			return *this;
		}

		Mat3 operator*(const double val)
		{
			Mat3 out(*this);
			out *= val;
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
					os << std::setw(10) << std::fixed << std::setprecision(5) << UNCONST_MAT3(matrix)[r][c] << ", ";
				}
				os << "]";
			}
			os << "\n:";
			return os;
		}

		TYPE Determinant() const
		{
			return  data_[0][0] * (data_[1][1] * data_[2][2] - data_[1][2] * data_[2][1]) -
					data_[0][1] * (data_[1][0] * data_[2][2] - data_[1][2] * data_[2][0]) +
					data_[0][2] * (data_[1][0] * data_[2][1] - data_[1][1] * data_[2][0]);
		}

		Mat3 GetTranspose() const
		{
			return { {data_[0][0], data_[1][0], data_[2][0]},
					 {data_[0][1], data_[1][1], data_[2][1]},
					 {data_[0][2], data_[1][2], data_[2][2]} };
		}

		Mat3& Transpose()
		{
			return (*this = GetTranspose());
		}

		Mat3 GetInverse() const
		{
			double determinant = Determinant();
			if (determinant != 0)
			{
				Mat3 adjugate{ {(data_[1][1] * data_[2][2] - data_[1][2] * data_[2][1]), -(data_[0][1] * data_[2][2] - data_[0][2] * data_[2][1]), (data_[0][1] * data_[1][2] - data_[0][2] * data_[1][1])},
								{-(data_[1][0] * data_[2][2] - data_[1][2] * data_[2][0]), (data_[0][0] * data_[2][2] - data_[0][2] * data_[2][0]), -(data_[0][0] * data_[1][2] - data_[0][2] * data_[1][0])},
								{(data_[1][0] * data_[2][1] - data_[1][1] * data_[2][0]), -(data_[0][0] * data_[2][1] - data_[0][1] * data_[2][0]), (data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0])} };
				return adjugate * (1.0 / determinant);
			}
			Log::Warning("Math", "Attempting to calculate inverse of singular 3x3 matrix. [DNE] Returning identity.");
			return Identity();
		}
	};

	template <typename TYPE>
	struct Mat4
	{
		TYPE data_[4][4] = { { 1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };

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
		template <typename INCOMING_TYPE>
		Mat4(const Mat4<INCOMING_TYPE>& mat4)
		{
			data_[0][0] = static_cast<TYPE>(mat4.data_[0][0]);
			data_[0][1] = static_cast<TYPE>(mat4.data_[0][1]);
			data_[0][2] = static_cast<TYPE>(mat4.data_[0][2]);
			data_[0][3] = static_cast<TYPE>(mat4.data_[0][3]);
			data_[1][0] = static_cast<TYPE>(mat4.data_[1][0]);
			data_[1][1] = static_cast<TYPE>(mat4.data_[1][1]);
			data_[1][2] = static_cast<TYPE>(mat4.data_[1][2]);
			data_[1][3] = static_cast<TYPE>(mat4.data_[1][3]);
			data_[2][0] = static_cast<TYPE>(mat4.data_[2][0]);
			data_[2][1] = static_cast<TYPE>(mat4.data_[2][1]);
			data_[2][2] = static_cast<TYPE>(mat4.data_[2][2]);
			data_[2][3] = static_cast<TYPE>(mat4.data_[2][3]);
			data_[3][0] = static_cast<TYPE>(mat4.data_[3][0]);
			data_[3][1] = static_cast<TYPE>(mat4.data_[3][1]);
			data_[3][2] = static_cast<TYPE>(mat4.data_[3][2]);
			data_[3][3] = static_cast<TYPE>(mat4.data_[3][3]);
		}

		static Mat4 Identity()
		{
			return { { 1.0,0.0,0.0,0.0},{0.0,1.0,0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0} };
		}

		static Mat4 Scale(TYPE x, TYPE y, TYPE z)
		{
			return static_cast<Mat4>(Mat3<TYPE>::Scale(x, y, z));
		}

		static Mat4 RotateX(double radian)
		{
			return static_cast<Mat4>(Mat3<TYPE>::RotateX(radian));
		}

		static Mat4 RotateY(double radian)
		{
			return static_cast<Mat4>(Mat3<TYPE>::RotateY(radian));
		}

		static Mat4 RotateZ(double radian)
		{
			return static_cast<Mat4>(Mat3<TYPE>::RotateZ(radian));
		}

		static Mat4 Translate(TYPE x, TYPE y, TYPE z)
		{
			return { {1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1} };
		}

		explicit operator Mat2<TYPE>() const
		{
			return { {data_[0][0],data_[0][1]}, {data_[1][0],data_[1][1]} };
		}

		explicit operator Mat3<TYPE>() const
		{
			return { {data_[0][0],data_[0][1],data_[0][2]}, {data_[1][0],data_[1][1],data_[1][2]}, {data_[2][0],data_[2][1],data_[2][2]} };
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

		Mat4& operator*=(const double val)
		{
			data_[0][0] *= val;
			data_[0][1] *= val;
			data_[0][2] *= val;
			data_[0][3] *= val;
			data_[1][0] *= val;
			data_[1][1] *= val;
			data_[1][2] *= val;
			data_[1][3] *= val;
			data_[2][0] *= val;
			data_[2][1] *= val;
			data_[2][2] *= val;
			data_[2][3] *= val;
			data_[3][0] *= val;
			data_[3][1] *= val;
			data_[3][2] *= val;
			data_[3][3] *= val;
			return *this;
		}

		Mat4 operator*(const double val) const
		{
			Mat4 out(*this);
			out *= val;
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

		template <typename VEC_TYPE>
		Vec4<TYPE> operator*(const Vec4<VEC_TYPE>& rhs) const
		{
			return { data_[0][0] * static_cast<TYPE>(rhs.x) + data_[0][1] * static_cast<TYPE>(rhs.y) + data_[0][2] * static_cast<TYPE>(rhs.z) + data_[0][3] * static_cast<TYPE>(rhs.w),
					 data_[1][0] * static_cast<TYPE>(rhs.x) + data_[1][1] * static_cast<TYPE>(rhs.y) + data_[1][2] * static_cast<TYPE>(rhs.z) + data_[1][3] * static_cast<TYPE>(rhs.w),
					 data_[2][0] * static_cast<TYPE>(rhs.x) + data_[2][1] * static_cast<TYPE>(rhs.y) + data_[2][2] * static_cast<TYPE>(rhs.z) + data_[2][3] * static_cast<TYPE>(rhs.w),
					 data_[3][0] * static_cast<TYPE>(rhs.x) + data_[3][1] * static_cast<TYPE>(rhs.y) + data_[3][2] * static_cast<TYPE>(rhs.z) + data_[3][3] * static_cast<TYPE>(rhs.w) };
		}

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
					os << std::setw(10) << std::fixed << std::setprecision(5) << UNCONST_MAT4(matrix)[r][c] << ", ";
				}
				os << "]";
			}
			os << "\n:";
			return os;
		}

		TYPE Determinant() const
		{
			Mat3 minor_0 {  {data_[1][1], data_[1][2], data_[1][3]},
							{data_[2][1], data_[2][2], data_[2][3]},
							{data_[3][1], data_[3][2], data_[3][3]} };

			Mat3 minor_1 {  {data_[1][0], data_[1][2], data_[1][3]},
							{data_[2][0], data_[2][2], data_[2][3]},
							{data_[3][0], data_[3][2], data_[3][3]} };

			Mat3 minor_2 {  {data_[1][0], data_[1][1], data_[1][3]},
							{data_[2][0], data_[2][1], data_[2][3]},
							{data_[3][0], data_[3][1], data_[3][3]} };

			Mat3 minor_3 {  {data_[1][0], data_[1][1], data_[1][2]},
							{data_[2][0], data_[2][1], data_[2][2]},
							{data_[3][0], data_[3][1], data_[3][2]} };

			return  data_[0][0] * minor_0.Determinant() -
					data_[0][1] * minor_1.Determinant() +
					data_[0][2] * minor_2.Determinant() -
					data_[0][3] * minor_3.Determinant();
		}

		Mat4 GetTranspose() const
		{
			return { {data_[0][0], data_[1][0], data_[2][0], data_[3][0]},
					 {data_[0][1], data_[1][1], data_[2][1], data_[3][1]},
					 {data_[0][2], data_[1][2], data_[2][2], data_[3][2]},
					 {data_[0][3], data_[1][3], data_[2][3], data_[3][3]} };
		}

		Mat4& Transpose()
		{
			return (*this = GetTranspose());
		}

		#define a(a,b,c,d,e,f) data_[a][b]*data_[c][d]*data_[e][f]

		Mat4 GetInverse() const
		{
			double determinant = Determinant();
			if (determinant != 0)
			{
				Mat4 adjugate{  { {a(1,1,2,2,3,3) + a(1,2,2,3,3,1) + a(1,3,2,1,3,2) - a(1,3,2,2,3,1) - a(1,2,2,1,3,3) - a(1,1,2,3,3,2)},
								{-a(0,1,2,2,3,3) - a(0,2,2,3,3,1) - a(0,3,2,1,3,2) + a(0,3,2,2,3,1) + a(0,2,2,1,3,3) + a(0,1,2,3,3,2)},
								{a(0,1,1,2,3,3) + a(0,2,1,3,3,1) + a(0,3,1,1,3,2) - a(0,3,1,2,3,1) - a(0,2,1,1,3,3) - a(0,1,1,3,3,2)},
								{-a(0,1,1,2,2,3) - a(0,2,1,3,2,1) - a(0,3,1,1,2,2) + a(0,3,1,2,2,1) + a(0,2,1,1,2,3) + a(0,1,1,3,2,2)} },

								{ {-a(1,0,2,2,3,3) - a(1,2,2,3,3,0) - a(1,3,2,0,3,2) + a(1,3,2,2,3,0) + a(1,2,2,0,3,3) + a(1,0,2,3,3,2)},
								{a(0,0,2,2,3,3) + a(0,2,2,3,3,0) + a(0,3,2,0,3,2) - a(0,3,2,2,3,0) - a(0,2,2,0,3,3) - a(0,0,2,3,3,2)},
								{-a(0,0,1,2,3,3) - a(0,2,1,3,3,0) - a(0,3,1,0,3,2) + a(0,3,1,2,3,0) + a(0,2,1,0,3,3) + a(0,0,1,3,3,2)},
								{a(0,0,1,2,2,3) + a(0,2,1,3,2,0) + a(0,3,1,0,2,2) - a(0,3,1,2,2,0) - a(0,2,1,0,2,3) - a(0,0,1,3,2,2)} },

								{ {a(1,0,2,1,3,3) + a(1,1,2,3,3,0) + a(1,3,2,0,3,1) - a(1,3,2,1,3,0) - a(1,1,2,0,3,3) - a(1,0,2,3,3,1)},
								{-a(0,0,2,1,3,3) - a(0,1,2,3,3,0) - a(0,3,2,0,3,1) + a(0,3,2,1,3,0) + a(0,1,2,0,3,3) + a(0,0,2,3,3,1)},
								{a(0,0,1,1,3,3) + a(0,1,1,3,3,0) + a(0,3,1,0,3,1) - a(0,3,1,1,3,0) - a(0,1,1,0,3,3) - a(0,0,1,3,3,1)},
								{-a(0,0,1,1,2,3) - a(0,1,1,3,2,0) - a(0,3,1,0,2,1) + a(0,3,1,1,2,0) + a(0,1,1,0,2,3) + a(0,0,1,3,2,1)} },

								{ {-a(1,0,2,1,3,2) - a(1,1,2,2,3,0) - a(1,2,2,0,3,1) + a(1,2,2,1,3,0) + a(1,1,2,0,3,2) + a(1,0,2,2,3,1)},
								{a(0,0,2,1,3,2) + a(0,1,2,2,3,0) + a(0,2,2,0,3,1) - a(0,2,2,1,3,0) - a(0,1,2,0,3,2) - a(0,0,2,2,3,1)},
								{-a(0,0,1,1,3,2) - a(0,1,1,2,3,0) - a(0,2,1,0,3,1) + a(0,2,1,1,3,0) + a(0,1,1,0,3,2) + a(0,0,1,2,3,1)},
								{a(0,0,1,1,2,2) + a(0,1,1,2,2,0) + a(0,2,1,0,2,1) - a(0,2,1,1,2,0) - a(0,1,1,0,2,2) - a(0,0,1,2,2,1)} }};
				return adjugate * (1.0 / determinant);
			}
			Log::Warning("Math", "Attempting to calculate inverse of singular 4x4 matrix. [DNE] Returning identity.");
			return Identity();
		}

		Mat4& Inverse()
		{
			return (*this = GetInverse());
		}
	};

	typedef Mat2<int> Mat2i;
	typedef Mat3<int> Mat3i;
	typedef Mat4<int> Mat4i;

	typedef Mat2<float> Mat2f;
	typedef Mat3<float> Mat3f;
	typedef Mat4<float> Mat4f;

	typedef Mat2<double> Mat2d;
	typedef Mat3<double> Mat3d;
	typedef Mat4<double> Mat4d;

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