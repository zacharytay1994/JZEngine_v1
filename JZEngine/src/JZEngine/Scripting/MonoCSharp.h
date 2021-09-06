#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace JZEngine
{
	struct MonoCSharp
	{
		MonoCSharp();

	private:
		MonoDomain* mono_domain_;
	};
}