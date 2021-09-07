#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace JZEngine
{
	enum class ShaderType
	{
		NONE = -1 ,
		VERTEX = 0 ,
		FRAGMENT = 1
	};

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Renderer
	{
	public:
		//struct GLModel
		//{
		//	GLenum		primitive_type;	
		//	GLuint		vaoid;			
		//	GLuint		idx_elem_cnt;	
		//};

		//GLModel Model_Data_ ;
		void SetupVao ();
		void Draw ();
	};

}