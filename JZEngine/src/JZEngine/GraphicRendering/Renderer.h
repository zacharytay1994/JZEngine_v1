#pragma once

#include <string>

namespace JZEngine
{

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Renderer
	{
	public:
		
		void SetupVao ();
		void Draw ();
	};

}