/*	__FILE HEADER__
*	File:		Vec2.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Custom Vec2 type.
*/

#pragma once

#include "../BuildDefinitions.h"
#include <iostream>

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
			return Vec2<T1> ( ( T1 ) x , ( T1 ) y );
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
			auto length = Len ();
			x /= ( T ) length;
			y /= ( T ) length;
			return *this;
		}

		Vec2 <float> GetNormalized () const
		{
			auto norm = *this;
			norm.Normalize ();
			return norm;
		}

		T Dot(const Vec2<T>& v) const
		{
			return x * v.x + y * v.y;
		}

		template <typename T1>
		auto operator + ( const Vec2<T1>& rhs )
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return Vec2<T2> ( x + rhs.x , y + rhs.y );
		}

		template <typename T1>
		auto operator + (const Vec2<T1>& rhs) const
		{
			typedef std::conditional < (std::is_integral<T>::value), T1, T >::type T2;
			return Vec2<T2>(x + rhs.x, y + rhs.y);
		}

		/*
		template <typename T>
		auto operator + (const Vec2<T>& rhs)
		{
			return Vec2<T2>(x + rhs.x, y + rhs.y);
		}
		*/
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
		auto operator * ( const T1& arg ) const
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return Vec2<T2> ( x * arg , y * arg ) ;
		}
		template <>
		auto operator * <float> (const float& arg) const
		{
			return Vec2<float>(x * arg, y * arg);
		}
		

		template <typename T1>
		auto operator / ( const T1& arg ) const
		{
			typedef std::conditional < ( std::is_integral<T>::value ) , T1 , T >::type T2;
			return Vec2<T2> ( x / arg , y / arg );
		}

		template <typename T1>
		Vec2& operator = ( const Vec2<T1>& rhs )
		{
			x = rhs.x ;
			y = rhs.y ;
			return *this ;
		}

		template <typename T1>
		Vec2& operator += ( const Vec2<T1>& rhs )
		{
			x += rhs.x ;
			y += rhs.y ;
			return *this ;
		}

		template <typename T1>
		Vec2& operator += ( const T1& arg )
		{
			x += arg;
			y += arg;
			return *this ;
		}

		template <typename T1>
		Vec2& operator -= ( const Vec2<T1>& rhs )
		{
			x -= rhs.x ;
			y -= rhs.y ;
			return *this ;
		}

		template <typename T1>
		Vec2& operator *= ( const T1 & arg )
		{
			x *= arg;
			y *= arg;
			return *this ;
		}

		template <typename T1>
		Vec2& operator /= ( const T1& arg )
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
	};

	template<typename T>
	std::ostream& operator<<( std::ostream& os , const Vec2<T>& arg )
	{
		os << "[" << arg.x << "," << arg.y << "]";
		return os;
	}
	template<typename T>
	Vec2<T> operator*(T lhs, const Vec2<T>& rhs)
	{
		return Vec2<T>(lhs * rhs.x, lhs * rhs.y);
	}

	typedef Vec2<int> Vec2i;
	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;
}
