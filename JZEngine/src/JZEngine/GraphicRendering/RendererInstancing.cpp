/*	__FILE HEADER__
*	File:		RendererInstancing.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Renders all instanced sprites.
*/

#include <PCH.h>
#include "RendererInstancing.h"
#include "../Math/JZMath.h"
#include "VertexBufferLayout.h"

namespace JZEngine
{
	RendererInstancing::RendererInstancing ()
		:
		instance_vb ( sizeof ( JZEngine::Mat3f )* MAX_BUFFER_TRANSFORMS )
	{}

	void RendererInstancing::Init ()
	{
		resource_manager_ = GetSystem<ResourceManager> ();
		VertexBuffer vb ( vertices.data () , static_cast< unsigned int >( vertices.size () * sizeof ( float ) ) );

		VertexBufferLayout layout;
		layout.Push<float> ( 2 );
		layout.Push<float> ( 2 );
		va.AddBuffer ( vb , layout );

		// also set instance data
		VertexBufferLayout instance_layout;
		// this attribute comes from a different vertex buffer
		instance_layout.Push<float> ( 3 );
		instance_layout.Push<float> ( 3 );
		instance_layout.Push<float> ( 3 );
		va.AddBuffer ( 2 , instance_vb , instance_layout );
		// what makes this code interesting is the last line where we call glVertexAttribDivisor.
		glVertexAttribDivisor ( 2 , 1 ); // tell OpenGL this is an instanced vertex attribute.
		glVertexAttribDivisor ( 3 , 1 );
		glVertexAttribDivisor ( 4 , 1 );

		va.Unbind ();
		vb.Unbind ();
		instance_vb.Unbind ();
	}

	void RendererInstancing::Draw ()
	{
		Bind ();
		for( auto& gp : geometry_packets_ )
		{
			resource_manager_->instanced_shader_programs_[ gp.first.first ].shader_program_.Bind ();
			resource_manager_->texture2ds_[ gp.first.second ].texture2d_.Bind ();
			GeometryPacket& geometry = gp.second;
			// bind transforms MAX_BUFFER_TRANSFORMS at a time
			for( int start = 0; start < geometry.transforms_.size (); start += MAX_BUFFER_TRANSFORMS )
			{
				assert ( start < geometry.transforms_.size () );
				int size = std::min ( MAX_BUFFER_TRANSFORMS , static_cast< unsigned int >( geometry.transforms_.size () - start ) );
				instance_vb.SetData ( geometry.transforms_.data () + start , size * sizeof ( JZEngine::Mat3f ) );
				glDrawArraysInstanced ( GL_TRIANGLES , 0 , 6 , size ); // 100 triangles of 6 vertices each
			}
			resource_manager_->instanced_shader_programs_[ gp.first.first ].shader_program_.Unbind ();
		}
		instance_vb.Unbind ();
		Unbind ();
		for( auto& gp : geometry_packets_ )
		{
			gp.second.ClearTransforms ();
		}
	}

	void RendererInstancing::Bind ()
	{
		va.Bind ();
	}

	void RendererInstancing::Unbind ()
	{
		va.Unbind ();
	}

	Shader RendererInstancing::GetShaderProgram ()
	{
		return shader_program;
	}

	void RendererInstancing::AddTransform ( int shader , int texture , const JZEngine::Mat3f& transform )
	{
		geometry_packets_[ {shader , texture} ].AddTransform ( transform );
	}
}