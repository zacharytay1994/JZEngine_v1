#pragma once

#include <tuple>

namespace JZEngine
{
	namespace Tuple
	{
		template <size_t I, typename TUPLE>
		std::tuple_element_t<I, TUPLE> GetType()
		{
			return std::tuple_element_t<I, TUPLE>();
		}
	}
}