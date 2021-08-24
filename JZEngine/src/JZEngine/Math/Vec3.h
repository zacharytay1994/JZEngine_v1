#pragma once

#include "../BuildDefinitions.h"
#include <iostream>
#include "Vec2.h"

namespace JZEngine
{
	template <typename T >
	struct Vec3 : public Vec2<T>
	{
		T x{};
		T y{};
		T z{};

		Vec3 () = default ;
		Vec3 ( T x , T y , T z )
			:
			x{ x } ,
			y{ y } ,
			z{ z }
		{}
		Vec3 ( const Vec3& rhs )
			:
			x{ rhs.x } ,
			y{ rhs.y } ,
			z{ rhs.z }
		{}
		template <typename T1>
		operator Vec3 <T1> () const
		{
			return Vec3 <T1> ( x , y , z );
		}

		auto LenSq () const
		{
			return ( x * x ) + ( y * y ) + ( z * z );
		}

		auto Len () const
		{
			return sqrt ( LenSq () );
		}

		Vec3& Normalize ()
		{
			auto length = Len ();
			x /= length;
			y /= length;
			z /= length;
			return *this;
		}

		Vec3 GetNormalized () const
		{
			Vec3 norm = *this ;
			norm.Normalize ();
			return norm;
		}

		Vec3& operator+=( const Vec3& rhs )
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		Vec3& operator-=( const Vec3& rhs )
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		Vec3& operator*=( const T& rhs )
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		Vec3& operator/=( const T& rhs )
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		Vec3 operator + ( const Vec3& rhs ) const
		{
			return Vec3 ( *this ) += rhs;
		}

		Vec3 operator - () const
		{
			return Vec3 ( -x , -y , -z );
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
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}

		Vec3 operator / ( const T& rhs ) const
		{
			return Vec3 ( *this ) /= rhs;
		}

		Vec3 operator % ( const Vec3& rhs ) const
		{
			return Vec3 (
				y * rhs.z - z * rhs.y ,
				z * rhs.x - x * rhs.z ,
				x * rhs.y - y * rhs.x );
		}

		Vec3& operator = ( const Vec3& rhs )
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}
		bool	operator==( const Vec3& rhs ) const
		{
			return x == rhs.x && y == rhs.y && rhs.z == z;
		}
		bool	operator!=( const Vec3& rhs ) const
		{
			return !( *this == rhs );
		}

	};
}