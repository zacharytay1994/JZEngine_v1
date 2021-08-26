#pragma once
#include <tuple>

#include "../ECSSystems/ExampleSingleHeader.h"
#include "../ECSSystems/ExampleSplitHeaderSource.h"

namespace JZEngine
{
	namespace ECS
	{
		struct ECSConfig
		{
			// add your structs/classes here that you want to be treated as Components
			using Component =
				std::tuple<
				
				TestComponent,
				TestComponent2,
				TestComponent3,
				Transform,
				MyNewComponent

				>;

			// add your structs/classes here that you want to be treated as Systems
			using System =
				std::tuple<
				
				TestSystem,
				TestSystem2,
				MyNewSystem
				
				>;
		};
	}
}