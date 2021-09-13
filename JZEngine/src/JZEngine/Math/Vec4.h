#include <iostream>
#include <algorithm>
#include "Vec3.h"

namespace JZEngine
{
	template < typename T>
	struct Vec4;

	template < typename T>
	std::ostream& operator << (std::ostream& os, const Vec4<T>& arg);

	template <typename T >
	struct Vec4 : public Vec3<T>
	{
		T w{};

		Vec4() = default;

		Vec4(T x, T y, T z, T w)
			:
			Vec3<T>(x, y, z),
			w{ w }
		{}

		Vec4(const Vec4& rhs)
			:
			Vec3<T>(rhs.x, rhs.y, rhs.z),
			w{ rhs.w }
		{}

		template <typename T1>
		operator Vec4 <T1>() const
		{
			return Vec4 <T1>(this->x, this->y, this->z, w);
		}

		auto LenSq() const
		{
			return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
		}

		auto Len() const
		{
			return sqrt(LenSq());
		}

		Vec4& Normalize()
		{
			auto length = Len();
			this->x = static_cast<T>(this->x / length);
			this->y = static_cast<T>(this->y / length);
			this->z = static_cast<T>(this->z / length);
			w = static_cast<T>(w / length);
			return *this;
		}

		Vec4 GetNormalized() const
		{
			Vec4 norm = *this;
			norm.Normalize();
			return norm;
		}

		template <typename T1>
		Vec4& operator+=(const Vec4<T1>& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			w += rhs.w;
			return *this;
		}

		template <typename T1>
		Vec4& operator+=(const T1& rhs)
		{
			this->x += rhs;
			this->y += rhs;
			this->z += rhs;
			w += rhs;
			return *this;
		}

		template <typename T1>
		Vec4& operator-=(const Vec4<T1>& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		template <typename T1>
		Vec4& operator*=(const T1& rhs)
		{
			this->x *= rhs;
			this->y *= rhs;
			this->z *= rhs;
			w *= rhs;
			return *this;
		}

		template <typename T1>
		Vec4& operator/=(const T1& rhs)
		{
			this->x /= rhs;
			this->y /= rhs;
			this->z /= rhs;
			w /= rhs;
			return *this;
		}

		Vec4 operator + (const Vec4& rhs) const
		{
			return Vec4(*this) += rhs;
		}

		Vec4 operator - () const
		{
			return Vec4(-this->x, -this->y, -this->z, w);
		}

		Vec4 operator - (const Vec4& rhs) const
		{
			return Vec4(*this) -= rhs;
		}

		Vec4 operator * (const T& rhs) const
		{
			return Vec4(*this) *= rhs;
		}

		T operator * (const Vec4& rhs) const
		{
			return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z + w * rhs.w;
		}

		Vec4 operator / (const T& rhs) const
		{
			return Vec4(*this) /= rhs;
		}

		Vec4 operator % (const Vec4& rhs) const
		{
			/*return Vec4(
				this->y * rhs.z - z * rhs.y,
				z * rhs.x - this->x * rhs.z,
				this->x * rhs.y - this->y * rhs.x,
				);*/
			return *this;
		}

		Vec4& operator = (const Vec4& rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			w = rhs.w;
			return *this;
		}

		bool	operator==(const Vec4& rhs) const
		{
			return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z && w == rhs.w;
		}

		bool	operator!=(const Vec4& rhs) const
		{
			return !(*this == rhs);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const Vec4<T>& arg)
	{
		os << "[" << arg.x << "," << arg.y << "," << arg.z << "," << arg.w << "]";
		return os;
	}

	typedef Vec4<int> Vec4i;
	typedef Vec4<float> Vec4f;
	typedef Vec4<double> Vec4d;
}