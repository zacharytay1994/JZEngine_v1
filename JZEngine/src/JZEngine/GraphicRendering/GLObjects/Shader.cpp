/*	__FILE HEADER__
*	File:		Shader.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Handles OpenGL shader program.
*/

#include <PCH.h>
#include "Shader.h"

namespace JZEngine
{
	Shader::Shader ()
		: pgm_handle ( 0 ) , is_linked ( GL_FALSE )
	{}

	GLboolean Shader::CompileShaderFromFile ( GLenum shader_type , const std::string& file_name )
	{
		if( GL_FALSE == FileExists ( file_name ) )
		{
			log_string = "File not found";
			return GL_FALSE;
		}

		if( pgm_handle <= 0 )
		{
			pgm_handle = glCreateProgram ();
			if( 0 == pgm_handle )
			{
				log_string = "Cannot create program handle";
				return GL_FALSE;
			}
		}

		std::ifstream shader_file ( file_name , std::ifstream::in );
		if( !shader_file )
		{
			log_string = "Error opening file " + file_name;
			return GL_FALSE;
		}

		std::stringstream buffer;
		buffer << shader_file.rdbuf ();
		shader_file.close ();
		return CompileShaderFromString ( shader_type , buffer.str () );
	}

	GLboolean Shader::CompileShaderFromString ( GLenum shader_type , std::string const& shader_src )
	{
		if( pgm_handle <= 0 )
		{
			pgm_handle = glCreateProgram ();
			if( 0 == pgm_handle )
			{
				log_string = "Cannot create program handle";
				return GL_FALSE;
			}
		}

		GLuint shader_handle = 0;
		switch( shader_type )
		{
			case VERTEX_SHADER: shader_handle = glCreateShader ( GL_VERTEX_SHADER ); break;
			case FRAGMENT_SHADER: shader_handle = glCreateShader ( GL_FRAGMENT_SHADER ); break;
			case GEOMETRY_SHADER: shader_handle = glCreateShader ( GL_GEOMETRY_SHADER ); break;
			case TESS_CONTROL_SHADER: shader_handle = glCreateShader ( GL_TESS_CONTROL_SHADER ); break;
			case TESS_EVALUATION_SHADER: shader_handle = glCreateShader ( GL_TESS_EVALUATION_SHADER ); break;
				//case COMPUTE_SHADER: shader_handle = glCreateShader(GL_COMPUTE_SHADER); break;
			default:
				log_string = "Incorrect shader type";
				return GL_FALSE;
		}

		// load shader source code into shader object
		GLchar const* shader_code [] = { shader_src.c_str () };
		glShaderSource ( shader_handle , 1 , shader_code , NULL );

		// compile the shader
		glCompileShader ( shader_handle );

		// check compilation status
		GLint comp_result;
		glGetShaderiv ( shader_handle , GL_COMPILE_STATUS , &comp_result );
		if( GL_FALSE == comp_result )
		{
			log_string = "Vertex shader compilation failed\n";
			GLint log_len;
			glGetShaderiv ( shader_handle , GL_INFO_LOG_LENGTH , &log_len );
			if( log_len > 0 )
			{
				GLchar* log = new GLchar[ log_len ];
				GLsizei written_log_len;
				glGetShaderInfoLog ( shader_handle , log_len , &written_log_len , log );
				log_string += log;
				delete [] log;
			}
			return GL_FALSE;
		}
		else
		{
			// attach the shader to the program object
			glAttachShader ( pgm_handle , shader_handle );
			return GL_TRUE;
		}
	}

	GLboolean Shader::Link ()
	{
		if( GL_TRUE == is_linked )
		{
			return GL_TRUE;
		}
		if( pgm_handle <= 0 )
		{
			return GL_FALSE;
		}

		// link the various compiled shaders
		glLinkProgram ( pgm_handle );

		// verify the link status
		GLint lnk_status;
		glGetProgramiv ( pgm_handle , GL_LINK_STATUS , &lnk_status );
		if( GL_FALSE == lnk_status )
		{
			log_string = "Failed to link shader program\n";
			GLint log_len;
			glGetProgramiv ( pgm_handle , GL_INFO_LOG_LENGTH , &log_len );
			if( log_len > 0 )
			{
				GLchar* log_str = new GLchar[ log_len ];
				GLsizei written_log_len;
				glGetProgramInfoLog ( pgm_handle , log_len , &written_log_len , log_str );
				log_string += log_str;
				delete [] log_str;
			}
			return GL_FALSE;
		}
		return is_linked = GL_TRUE;
	}

	GLboolean Shader::IsLinked () const
	{
		return is_linked;
	}

	GLuint Shader::ShaderHandle () const
	{
		return pgm_handle;
	}

	std::string Shader::GetLog () const
	{
		return log_string;
	}

	void Shader::Bind () const
	{
		if( pgm_handle > 0 && is_linked == GL_TRUE )
		{
			glUseProgram ( pgm_handle );
		}
	}

	void Shader::Unbind () const
	{
		glUseProgram ( 0 );
	}

	void Shader::SetUniform ( GLchar const* name , GLboolean val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform1i ( loc , val );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , GLint val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform1i ( loc , val );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , GLfloat val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform1f ( loc , val );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , GLfloat x , GLfloat y )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform2f ( loc , x , y );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , GLfloat x , GLfloat y , GLfloat z )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform3f ( loc , x , y , z );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , GLfloat x , GLfloat y , GLfloat z , GLfloat w )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform4f ( loc , x , y , z , w );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , JZEngine::Vec2f const& val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform2f ( loc , val.x , val.y );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , JZEngine::Vec3f const& val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform3f ( loc , val.x , val.y , val.z );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , JZEngine::Vec4f const& val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniform4f ( loc , val.x , val.y , val.z , val.w );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , JZEngine::Mat3f const& val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniformMatrix3fv ( loc , 1 , GL_FALSE , val.data_[ 0 ] );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	void Shader::SetUniform ( GLchar const* name , JZEngine::Mat4f const& val )
	{
		GLint loc = glGetUniformLocation ( pgm_handle , name );
		if( loc >= 0 )
		{
			glUniformMatrix4fv ( loc , 1 , GL_FALSE , &val.data_[ 0 ][ 0 ] );
		}
		else
		{
			std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
		}
	}

	GLboolean Shader::FileExists ( std::string const& file_name )
	{
		std::ifstream infile ( file_name );
		return infile.good ();
	}
}
