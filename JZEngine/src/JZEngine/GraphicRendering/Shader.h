#pragma once

#include <string>
#include <glad/glad.h>


namespace JZEngine
{
	class Shader
	{
	public:

		Shader ();
		GLboolean CompileShaderFromFile ( GLenum shader_type , std::string const& file_name );
		GLboolean CompileShaderFromString ( GLenum shader_type , std::string const& shader_src );
		GLboolean Link ();
		GLboolean IsLinked () const;
		std::string GetLog () const;
		void Bind () const;
		void Unbind () const;


		void SetUniform ( GLchar const* name , GLboolean val );
		void SetUniform ( GLchar const* name , GLint val );
		void SetUniform ( GLchar const* name , GLfloat val );
		void SetUniform ( GLchar const* name , GLfloat x , GLfloat y );
		void SetUniform ( GLchar const* name , GLfloat x , GLfloat y , GLfloat z );
		void SetUniform ( GLchar const* name , GLfloat x , GLfloat y , GLfloat z , GLfloat w );
		//void SetUniform ( GLchar const* name , glm::vec2 const& val );
		//void SetUniform ( GLchar const* name , glm::vec3 const& val );
		//void SetUniform ( GLchar const* name , glm::mat3 const& val );
		//void SetUniform ( GLchar const* name , glm::mat4 const& val );

	
	private:

		enum ShaderType
		{
			VERTEX_SHADER = GL_VERTEX_SHADER ,
			FRAGMENT_SHADER = GL_FRAGMENT_SHADER ,
			GEOMETRY_SHADER = GL_GEOMETRY_SHADER ,
			TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER ,
			TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER ,
		};
		GLuint pgm_handle = 0;  // handle to linked shader program object
		GLboolean is_linked = GL_FALSE; // has the program successfully linked?
		std::string log_string; // log for OpenGL compiler and linker messages

	private :

		GLboolean FileExists ( std::string const& file_name );
	}; 

}