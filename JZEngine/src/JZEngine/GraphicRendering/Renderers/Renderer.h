/*	__FILE HEADER__
*	File:		Renderer.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Bind VAO , VBO , IBO and Shader .
*/

#pragma once

#include <memory>
#include <array>
#include "../GLObjects/Buffer.h"
#include "../GLObjects/Shader.h"
#include "../GLObjects/VertexArray.h"
#include "../GLObjects/VertexBufferLayout.h"
#include "../../Resource/ResourceManager.h"

#include "../GLObjects/Texture.h"
#include <unordered_map>


namespace JZEngine
{
	class Renderer
	{
	private:

		/*set up vertex data ( and buffer ( s ) ) and configure vertex attributes
			------------------------------------------------------------------*/
		std::array < float , 32 > vertices
		{
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};

		std::array < unsigned int , 6 > indices
		{  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		Shader shader_program;
		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		std::unordered_map<std::string , Texture2D> textures_;

	public:

		Renderer ();

		void Initialize ();
		void Draw ();
		void Draw ( int frame , int row , int col );
		void Bind ();
		void Unbind ();
		void Clear ();

		Shader& GetShaderProgram ( ResourceManager* resource_manager_, int shaderid );
		void BindTexture ( const std::string& name );
		void BindTexture ( ResourceManager* resource_manager_, int textureid );
		void BindShader ( ResourceManager* resource_manager_, int shaderid );
		void UnbindShader ( ResourceManager* resource_manager_, int shaderid );

	};
}