#pragma once

#include "../BuildDefinitions.h"

#include <iostream>
#include <type_traits>
#include <typeinfo>

namespace JZEngine
{
	template < typename T>
	struct Vec2;

	template < typename T>
	std::ostream& operator << ( std::ostream& os , const Vec2<T>& arg );

	template < typename T>
	struct Vec2
	{

		T x{ 0 };
		T y{ 0 };

		Vec2 ()
			: x{ 0 } , y{ 0 }
		{}
		Vec2 ( T x , T y )
			: x{ x } , y{ y }
		{}
		Vec2 ( const Vec2& rhs )
			: x{ rhs.x } , y{ rhs.y }
		{}

		template <typename T1 >
		operator Vec2<T1> () const
		{
			return Vec2<T1> ( x , y );
		}

		auto LenSq () const
		{
			return x * x + y * y;
		}

		auto Len () const
		{
			return sqrt ( LenSq () );
		}

		Vec2& Normalize ()
		{
			const auto length = Len ();
			x /= length;
			y /= length;
			return *this;
		}

		Vec2 <float> GetNormalized () const
		{
			auto norm = *this;
			norm.Normalize ();
			return norm;
		}

		template <typename T1>
		auto operator + ( const Vec2<T1>& rhs )
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return Vec2<T2> ( x + rhs.x , y + rhs.y );
		}
		template <typename T1>
		auto operator - ( const Vec2<T1>& rhs ) const
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return Vec2<T2> ( x - rhs.x , y - rhs.y );
		}

		Vec2 operator-() const
		{
			return { -x, -y };
		}

		template <typename T1>
		auto operator * ( const Vec2<T1>& rhs ) const
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return ( T2 ) ( x * rhs.x + y * rhs.y );
		}

		template <typename T1>
		auto operator * ( const T1& arg ) const
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return Vec2<T2> ( x * arg , y * arg ) ;
		}

		template <typename T1>
		auto operator / ( const T1& arg )
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return Vec2<T2> ( x / arg , y / arg );
		}

		Vec2& operator = ( const Vec2& rhs )
		{
			x = rhs.x ;
			y = rhs.y ;
			return *this ;
		}

		Vec2& operator += ( const Vec2& rhs )
		{
			x += rhs.x ;
			y += rhs.y ;
			return *this ;
		}

		Vec2& operator -= ( const Vec2& rhs )
		{
			x -= rhs.x ;
			y -= rhs.y ;
			return *this ;
		}

		Vec2& operator *= ( const T& arg )
		{
			x *= arg ;
			y *= arg ;
			return *this ;
		}

		Vec2& operator /= ( const T& arg )
		{
			x /= arg ;
			y /= arg ;
			return *this ;
		}

		bool operator == ( const Vec2& rhs ) const
		{
			return x == rhs.x && y == rhs.y;
		}

		bool operator != ( const Vec2& rhs ) const
		{
			return !( *this == rhs );
		}

		/*	Vec2 operator < ( const Vec2& rhs );
			Vec2 operator > ( const Vec2& rhs );*/

	};

	template<typename T>
	std::ostream& operator<<( std::ostream& os , const Vec2<T>& arg )
	{
		os << arg.x << "," << arg.y << " ";
		return os;
	}


}
