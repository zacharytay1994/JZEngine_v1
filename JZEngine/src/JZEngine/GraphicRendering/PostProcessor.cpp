#include "PCH.h"
#include "PostProcessor.h"



namespace JZEngine
{
	PostProcessor::PostProcessor ()
		:
		MSFBO ( 0 ) ,
		FBO ( 0 ) ,
		RBO ( 0 ) ,
		vb ( vertices.data () , static_cast< unsigned int >( vertices.size () * sizeof ( float ) ) )
	{}

	void PostProcessor::Init ( unsigned int width , unsigned int height )
	{
		width_ = width ;
		height_ = height ;

		// initialize renderbuffer/framebuffer object
		glGenFramebuffers ( 1 , &MSFBO );
		glGenFramebuffers ( 1 , &FBO );
		glGenRenderbuffers ( 1 , &RBO );
		// initialize renderbuffer storage with a multisampled color buffer (don't need a depth/stencil buffer)
		glBindFramebuffer ( GL_FRAMEBUFFER , MSFBO );
		glBindRenderbuffer ( GL_RENDERBUFFER , RBO );
		glRenderbufferStorageMultisample ( GL_RENDERBUFFER , 4 , GL_RGB , width_ , height_ ); // allocate storage for render buffer object
		glFramebufferRenderbuffer ( GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_RENDERBUFFER , RBO ); // attach MS render buffer object to framebuffer
		if( glCheckFramebufferStatus ( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
			std::cout << "ERROR::POSTPROCESSOR: Failed to initialize MSFBO" << std::endl;

		// also initialize the FBO/texture to blit multisampled color-buffer to; used for shader operations (for postprocessing effects)
		glBindFramebuffer ( GL_FRAMEBUFFER , FBO );

		texture_.Texture2DLoad ( width_ , height_ );

		glFramebufferTexture2D ( GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D , texture_.GetRendererID () , 0 ); // attach texture to framebuffer as its color attachment

		if( glCheckFramebufferStatus ( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
			std::cout << "ERROR::POSTPROCESSOR: Failed to initialize FBO" << std::endl;

		glBindFramebuffer ( GL_FRAMEBUFFER , 0 );

		// initialize render data and uniforms
		initRenderData ();

		shader_program_.Bind ();

		shader_program_.SetUniform ( "scene" , 0 );
		float offset = 1.0f / 300.0f;
		float offsets[ 9 ][ 2 ] =
		{
			{ -offset,  offset  },  // top-left
			{  0.0f,    offset  },  // top-center
			{  offset,  offset  },  // top-right
			{ -offset,  0.0f    },  // center-left
			{  0.0f,    0.0f    },  // center-center
			{  offset,  0.0f    },  // center - right
			{ -offset, -offset  },  // bottom-left
			{  0.0f,   -offset  },  // bottom-center
			{  offset, -offset  }   // bottom-right    
		};

		glUniform2fv ( glGetUniformLocation ( shader_program_.ShaderHandle () , "offsets" ) , 9 , ( float* ) offsets );

		int edge_kernel[ 9 ] = {
			-1, -1, -1,
			-1,  8, -1,
			-1, -1, -1
		};

		glUniform1iv ( glGetUniformLocation ( shader_program_.ShaderHandle () , "edge_kernel" ) , 9 , edge_kernel );

		float blur_kernel[ 9 ] = 
		{
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
			2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
			1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
		};

		glUniform1fv ( glGetUniformLocation ( shader_program_.ShaderHandle () , "blur_kernel" ) , 9 , blur_kernel );

	}

	void PostProcessor::Bind ()
	{
		glBindFramebuffer ( GL_FRAMEBUFFER , MSFBO );
		glClearColor ( 0.0f , 0.0f , 0.0f , 1.0f );
		glClear ( GL_COLOR_BUFFER_BIT );
	}

	void PostProcessor::Unbind ()
	{
		glBindFramebuffer ( GL_READ_FRAMEBUFFER , MSFBO );
		glBindFramebuffer ( GL_DRAW_FRAMEBUFFER , FBO );
		glBlitFramebuffer ( 0 , 0 , width_ , height_ , 0 , 0 , width_ , height_ , GL_COLOR_BUFFER_BIT , GL_NEAREST );
		glBindFramebuffer ( GL_FRAMEBUFFER , 0 ); // binds both READ and WRITE framebuffer to default framebuffer
	}

	void PostProcessor::Render ( float time )
	{
		shader_program_.Bind ();
		shader_program_.SetUniform ( "time" , time );
		shader_program_.SetUniform ( "confuse" , confuse_ );
		shader_program_.SetUniform ( "chaos" , chaos_ );
		shader_program_.SetUniform ( "shake" , shake_ );
		// render textured quad
		texture_.Bind ();
		va.Bind ();
		glDrawArrays ( GL_TRIANGLES , 0 , 6 );
		va.Unbind ();
		//glBindVertexArray ( 0 );
	}

	void PostProcessor::initRenderData ()
	{
		// configure VAO/VBO
		VertexBufferLayout layout;
		layout.Push<float> ( 4 );
		va.AddBuffer ( vb , layout );
		va.Unbind ();
		vb.Unbind ();

		shader_program_.CompileShaderFromFile ( GL_VERTEX_SHADER , "Assets/Shaders/Vertex/VS_Post_Processing.vs" );
		shader_program_.CompileShaderFromFile ( GL_FRAGMENT_SHADER , "Assets/Shaders/Fragment/FS_Post_Processing.fs" );
		shader_program_.Link ();

		if( GL_FALSE == shader_program_.IsLinked () )
		{
			std::cout << "Unable to compile/link/validate shader programs" << "\n";
			std::cout << shader_program_.GetLog () << std::endl;
			std::exit ( EXIT_FAILURE );
		}

		shader_program_.ActiveUniformsList ();
	}

}