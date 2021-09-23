#pragma once

#include <vector>
#include <string>

#include "../GlobalSystems.h"
#include "../GraphicRendering/Shader.h"
#include "../GraphicRendering/Texture.h"

namespace JZEngine
{
	struct ResourceManager : public GlobalSystem
	{
		struct ShaderID
		{
			const unsigned int id_;
			std::string name_;
			Shader shader_program_;

			ShaderID(unsigned int id, const std::string& name) : id_(id), name_(name) {}
		};

		struct InstancedShaderID
		{
			const unsigned int id_;
			std::string name_;
			Shader shader_program_;

			InstancedShaderID( unsigned int id, const std::string& name ) : id_( id ), name_( name )
			{}
		};

		struct Texture2DID
		{
			const unsigned int id_;
			std::string name_;
			Texture2D texture2d_;

			Texture2DID(unsigned int id, const std::string& name) : id_(id), name_(name) {}
		};

		std::vector<InstancedShaderID> instanced_shader_programs_;
		std::vector<ShaderID> shader_programs_;
		std::vector<Texture2DID> texture2ds_;

		ResourceManager();

		unsigned int LoadInstancedShader( const std::string& name, const std::string& vspath, const std::string& fspath );
		unsigned int LoadShader(const std::string& name, const std::string& vspath, const std::string& fspath);
		unsigned int LoadTexture2D(const std::string& name, const std::string& path);
	};
}