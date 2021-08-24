#pragma once
#include <tuple>

#include "testecs.h"

namespace JZEngine
{
	namespace ECS
	{
		struct ECSConfig
		{
			using Component =
				std::tuple<

				// ECS components
				TestComponent2,
				TestComponent,
				TestComponent3,
				Transform

				>;

			using System =
				std::tuple<
				
				TestSystem,
				TestSystem2
				
				>;
		};
	}
}