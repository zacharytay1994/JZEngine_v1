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