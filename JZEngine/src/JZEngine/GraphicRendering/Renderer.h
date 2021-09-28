/*	__FILE HEADER__
*	File:	Renderer.h
	Author: JZ
	Date:	01/07/21
	Brief:	Bind VAO , VBO , IBO and Shader .
*/

#pragma once

#include <memory>
#include <array>
#include "../GlobalSystems.h"
#include "Buffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "../Resource/ResourceManager.h"

#include "Texture.h"
#include <unordered_map>


namespace JZEngine
{
	class Renderer : public GlobalSystem
	{
	private:

		/*set up vertex data ( and buffer ( s ) ) and configure vertex attributes
			------------------------------------------------------------------*/
		std::array < float, 32 > vertices
		{
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};
		std::array < unsigned int, 6 > indices
		{  // note that we start from 0!
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		Shader shader_program;
		VertexArray va;
		IndexBuffer ib;
		std::unordered_map<std::string, Texture2D> textures_;

	public:

		Renderer();

		/*static Renderer& Instance()
		{
			static Renderer Instance;
			return Instance;
		};*/
		virtual void Init() override;
		void Draw();
		void Bind();
		void Unbind();
		void Clear();

		Shader& GetShaderProgram(int shaderid);
		void BindTexture(const std::string& name);
		void BindTexture(int textureid);
		void BindShader(int shaderid);
		void UnbindShader(int shaderid);

		ResourceManager* resource_manager_{nullptr};
	};
}