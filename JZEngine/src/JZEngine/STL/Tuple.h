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

		//template <size_t I = 0, typename...TUPLE>
		//typename std::enable_if<I == sizeof...(TUPLE), void>::type
		//	RegisterTuple(std::tuple<TUPLE...> t)
		//{
		//	// no more tuples to iterate over, return void
		//	return;
		//}

		//template <size_t I = 0, typename...TUPLE>
		//typename std::enable_if < I < sizeof...(TUPLE), void>::type
		//	RegisterTuple(std::tuple<TUPLE...> t)
		//{
		//	RegisterComponent<std::tuple_element_t<I, std::tuple<TUPLE...>>>();
		//	RegisterTuple<I + 1>(t);
		//}


		/*template <size_t I = 0, typename...TUPLE>
		typename std::enable_if<I == sizeof...(TUPLE), void>::type
		LoopTuple(std::tuple<TUPLE...> t, size_t i)
		{
			std::cout << "tuple size exceeded." << std::endl;
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		typename std::enable_if < I < sizeof...(TUPLE), void>::type
		LoopTuple(std::tuple<TUPLE...> t, size_t i)
		{
			if (I == i)
			{
				std::cout << "looptuple:: " << typeid(decltype(std::get<I>(t))).name() << std::endl;
				return;
			}
			LoopTuple<I+1>(t, i);
		}*/
	}
}