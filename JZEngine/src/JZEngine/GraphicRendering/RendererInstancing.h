/*	__FILE HEADER__
*	File:		RendererInstancing.h
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Instancing is a technique where we draw many (equal mesh data) object
				at once with a single render call, saving us all the CPU -> GPU
				communications each time we need to render an object.


				Fun Fact:
				For example, you can make a forest scene by creating 100 instances of a single tree asset.
				Each instance would be in a different position, with a slightly different size, and rotated
				a little bit. From the viewer’s perspective, it looks like 100 different trees.
				From the programmer’s perspective, it is actually just one tree that is drawn 100 times.
*/

#pragma once

#include <vector>
#include <array>
#include <assert.h>
#include <unordered_map>

#include "../GlobalSystems.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "../Math/JZMath.h"
#include "../Resource/ResourceManager.h"

namespace JZEngine
{
	class RendererInstancing : public GlobalSystem
	{
		Shader shader_program;
		VertexArray va;
		VertexBuffer instance_vb;

		static constexpr unsigned int MAX_BUFFER_TRANSFORMS = 500;
		static constexpr unsigned int MAX_INSTANCES = 50000;
		struct GeometryPacket
		{
			std::vector<JZEngine::Mat3f> transforms_;
			void ClearTransforms()
			{
				transforms_.clear();
			}
			void AddTransform( const JZEngine::Mat3f& transform )
			{
				transforms_.emplace_back( transform );
				assert( transforms_.size() < MAX_INSTANCES );
			}
		};

		struct pair_hash
		{
			template <class T1, class T2>
			std::size_t operator () ( const std::pair<T1, T2>& p ) const
			{
				auto h1 = std::hash<T1>{}( p.first );
				auto h2 = std::hash<T2>{}( p.second );

				// Mainly for demonstration purposes, i.e. works but is overly simple
				// In the real world, use sth. like boost.hash_combine
				return h1 ^ h2;
			}
		};
		std::unordered_map<std::pair<int, int>, GeometryPacket, pair_hash> geometry_packets_;

		std::array <float, 24>vertices
		{
			// positions		// textures
			-0.5f,  0.5f,		0.0f, 1.0f,
			 0.5f, -0.5f,		1.0f, 0.0f,
			-0.5f, -0.5f,		0.0f, 0.0f,

			-0.5f,  0.5f,		0.0f, 1.0f,
			 0.5f, -0.5f,		1.0f, 0.0f,
			 0.5f,  0.5f,		1.0f, 1.0f
		};

	public:
		RendererInstancing();
		
		virtual void Init() override;
		void Draw();
		void Bind();
		void Unbind();

		Shader GetShaderProgram();
		void AddTransform( int shader, int texture, const JZEngine::Mat3f& transform );

		ResourceManager* resource_manager_{ nullptr };
	};

}

