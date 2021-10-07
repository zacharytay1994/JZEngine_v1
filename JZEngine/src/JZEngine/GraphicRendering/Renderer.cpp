/*	__FILE HEADER__
*	File:		Renderer.cpp
	Primary:	Jee Jia Min
	Date:		26/08/21
	Brief:		Renderer handles all default sprites.
*/

#include <PCH.h>
#include <glad/glad.h>
#include "Renderer.h"

namespace JZEngine
{
	Renderer::Renderer ()
		:
		ib ( indices.data () , static_cast < unsigned int > ( indices.size () ) ) ,
		vb ( vertices.data () , static_cast< unsigned int >( vertices.size () * sizeof ( float ) ) )
	{
		// load all texture images
		//textures_["unicorn"].Texture2DLoad("Assets/Textures/cute-unicorn.png");
	};

	void Renderer::Init ()
	{
		resource_manager_ = GetSystem<ResourceManager> ();
		VertexBufferLayout layout;
		layout.Push<float> ( 3 );
		layout.Push<float> ( 3 );
		layout.Push<float> ( 2 );
		va.AddBuffer ( vb , layout );
		va.Unbind ();
		vb.Unbind ();
		ib.Unbind ();
	}

	void Renderer::Draw ( int frame , int row , int col )
	{
		// calculate x width
		int x_offset = frame % col;
		int y_offset = row - ( frame / row ) - 1;

		float width = 1.0f / col;
		float height = 1.0f / row;

		float min_x = x_offset * width;
		float max_x = min_x + width;
		float min_y = y_offset * height;
		float max_y = min_y + height;

		vertices[ 6 ] = max_x;
		vertices[ 7 ] = max_y;

		vertices[ 14 ] = max_x;
		vertices[ 15 ] = min_y;

		vertices[ 22 ] = min_x;
		vertices[ 23 ] = min_y;

		vertices[ 30 ] = min_x;
		vertices[ 31 ] = max_y;

		vb.SetData ( vertices.data () , 32 * sizeof ( float ) );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );
	}

	void Renderer::Draw ()
	{

		vertices[ 6 ] = 1.0f;
		vertices[ 7 ] = 1.0f;

		vertices[ 14 ] = 1.0f;
		vertices[ 15 ] = 0.0f;

		vertices[ 22 ] = 0.0f;
		vertices[ 23 ] = 0.0f;

		vertices[ 30 ] = 0.0f;
		vertices[ 31 ] = 1.0f;

		vb.SetData ( vertices.data () , 32 * sizeof ( float ) );
		glDrawElements ( GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0 );
	}

	void Renderer::Clear ()
	{
		glClear ( GL_COLOR_BUFFER_BIT );
	}

	void Renderer::Bind ()
	{
		va.Bind ();
		ib.Bind ();
	}

	void Renderer::Unbind ()
	{
		va.Unbind ();
		ib.Unbind ();
	}

	Shader& Renderer::GetShaderProgram ( int shaderid )
	{
		return resource_manager_->shader_programs_[ shaderid ].shader_program_;
	}

	void Renderer::BindTexture ( const std::string& name )
	{
		textures_[ name ].Bind ();
	}

	void Renderer::BindTexture ( int textureid )
	{
		resource_manager_->texture2ds_[ textureid ].texture2d_.Bind ();
	}

	void Renderer::BindShader ( int shaderid )
	{
		resource_manager_->shader_programs_[ shaderid ].shader_program_.Bind ();
	}

	void Renderer::UnbindShader ( int shaderid )
	{
		resource_manager_->shader_programs_[ shaderid ].shader_program_.Unbind ();
	}
}