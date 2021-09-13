#pragma once

#include "../BuildDefinitions.h"
#include <iostream>
#include <algorithm>
#include "Vec2.h"

namespace JZEngine
{
	template < typename T>
	struct Vec3;

	template < typename T>
	std::ostream& operator << ( std::ostream& os , const Vec3<T>& arg );

	template <typename T >
	struct Vec3 : public Vec2<T>
	{
		T z{};

		Vec3 () = default ;

		Vec3 ( T x , T y , T z )
			:
			Vec2<T> ( x , y ) ,
			z{ z }
		{}

		Vec3 ( const Vec3& rhs )
			:
			Vec2<T> ( rhs.x , rhs.y ) ,
			z{ rhs.z }
		{}

		template <typename T1>
		operator Vec3 <T1> () const
		{
			return Vec3 <T1> ( this->x , this->y , z );
		}

		auto LenSq () const
		{
			return ( this->x * this->x ) + ( this->y * this->y ) + ( z * z );
		}

		auto Len () const
		{
			return sqrt ( LenSq () );
		}

		Vec3& Normalize ()
		{
			auto length = Len ();
			this->x = static_cast<T>(this->x / length);
			this->y = static_cast<T>(this->y / length);
			z = static_cast<T>(z / length);
			return *this;
		}

		Vec3 GetNormalized () const
		{
			Vec3 norm = *this ;
			norm.Normalize ();
			return norm;
		}

		template <typename T1>
		Vec3& operator+=( const Vec3<T1>& rhs )
		{
			this->x += rhs.x;
			this->y += rhs.y;
			z += rhs.z;
			return *this;
		}

		template <typename T1>
		Vec3& operator+=( const T1& rhs )
		{
			this->x += rhs;
			this->y += rhs;
			z += rhs;
			return *this;
		}

		template <typename T1>
		Vec3& operator-=( const Vec3<T1>& rhs )
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		template <typename T1>
		Vec3& operator*=( const T1& rhs )
		{
			this->x *= rhs;
			this->y *= rhs;
			z *= rhs;
			return *this;
		}

		template <typename T1>
		Vec3& operator/=( const T1& rhs )
		{
			this->x /= rhs;
			this->y /= rhs;
			z /= rhs;
			return *this;
		}

		Vec3 operator + ( const Vec3& rhs ) const
		{
			return Vec3 ( *this ) += rhs;
		}

		Vec3 operator - () const
		{
			return Vec3 ( -this->x , -this->y , -z );
		}

		Vec3 operator - ( const Vec3& rhs ) const
		{
			return Vec3 ( *this ) -= rhs;
		}

		Vec3 operator * ( const T& rhs ) const
		{
			return Vec3 ( *this ) *= rhs;
		}

		T operator * ( const Vec3& rhs ) const
		{
			return this->x * rhs.x + this->y * rhs.y + z * rhs.z;
		}

		Vec3 operator / ( const T& rhs ) const
		{
			return Vec3 ( *this ) /= rhs;
		}

		Vec3 operator % ( const Vec3& rhs ) const
		{
			return Vec3 (
				this->y * rhs.z - z * rhs.y ,
				z * rhs.x - this->x * rhs.z ,
				this->x * rhs.y - this->y * rhs.x );
		}

		Vec3& operator = ( const Vec3& rhs )
		{
			this->x = rhs.x;
			this->y = rhs.y;
			z = rhs.z;
			return *this;
		}

		bool	operator==( const Vec3& rhs ) const
		{
			return this->x == rhs.x && this->y == rhs.y && rhs.z == z;
		}

		bool	operator!=( const Vec3& rhs ) const
		{
			return !( *this == rhs );
		}

	};

	template<typename T>
	std::ostream& operator<<( std::ostream& os , const Vec3<T>& arg )
	{
		os << "[" << arg.x << "," << arg.y << "," << arg.z << "]";
		return os;
	}

	typedef Vec3<int> Vec3i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<double> Vec3d;
}