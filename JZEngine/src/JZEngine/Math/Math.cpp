/*	__FILE HEADER__
*	File:		Math.cpp
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Custom Math Library.
*/

#include "Vec2.h"
#include "Vec3.h"

namespace JZEngine
{
	template struct JZENGINE_API Vec2<int>;
	template struct JZENGINE_API Vec2<float>;

	template struct JZENGINE_API Vec3<int>;
	template struct JZENGINE_API Vec3<float>;

	#ifndef PI
		#define	PI		3.1415926f
	#endif
}