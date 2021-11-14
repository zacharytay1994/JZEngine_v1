/*	__FILE HEADER__
*	File:		ResourceManager.h
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Manages all external assets.
*/

#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H // freetype.h

#include <map>
#include <vector>
#include <string>

#include "../GlobalSystems.h"
#include "../GraphicRendering/Shader.h"
#include "../GraphicRendering/Texture.h"
#include "../Sound/Sound.h"

namespace JZEngine
{
	struct ResourceManager : public GlobalSystem
	{
		struct ShaderID
		{
			const unsigned int id_;
			std::string name_;
			Shader shader_program_;

			ShaderID(unsigned int id, const std::string &name) : id_(id), name_(name) {}

			template <typename... PARAMS>
			void BindUniforms(std::initializer_list<std::string> uniformnames, PARAMS... params)
			{
				int i{0};
				//shader_program_.SetUniform(uniformnames[i], i);
				((shader_program_.SetUniform(uniformnames[i++], params)), ...);
			}
		};

		struct InstancedShaderID
		{
			const unsigned int id_;
			std::string name_;
			Shader shader_program_;

			InstancedShaderID(unsigned int id, const std::string &name) : id_(id), name_(name)
			{
			}
		};

		struct FontShaderID
		{
			const unsigned int id_;
			std::string name_;
			Shader shader_program_;

			FontShaderID(unsigned int id, const std::string &name) : id_(id), name_(name)
			{
			}
		};

		struct DebugShader
		{
			const unsigned int id_;
			std::string name_;
			Shader shader_program_;

			DebugShader(unsigned int id, const std::string &name) : id_(id), name_(name)
			{
			}
		};

		struct Texture2DID
		{
			int id_{-1};
			Texture2D texture2d_;

			Texture2DID(int id) : id_(id) {}
		};

		struct FontID
		{
			const unsigned int id_;
			std::string name_;
			Texture2D texture2d_;

			FontID(unsigned int id, const std::string &name) : id_(id), name_(name)
			{
			}
		};

		struct SoundID
		{
			int id_;
			std::string name_;
			SoundSystem sound_system_;

			SoundID(unsigned int id, const std::string &name) : id_(id), name_(name)
			{
			}
		};

		std::vector<FontShaderID> font_shader_programs_;
		std::vector<FontID> text_;

		/*ResourceManager();

		unsigned int LoadInstancedShader( const std::string& name, const std::string& vspath, const std::string& fspath );*/
		unsigned int LoadFontShader(const std::string &name, const std::string &vspath, const std::string &fspath);
		/*unsigned int LoadShader(const std::string& name, const std::string& vspath, const std::string& fspath);
		unsigned int LoadTexture2D(const std::string& name, const std::string& path);*/

		// FONT RESOURCE
		// Holds all state information relevant to a character as loaded using FreeType
		struct Character
		{
			FT_Face face_{};
			unsigned int texture_id_{0};		  // ID handle of the glyph texture
			JZEngine::Vec2f size_{1.0f, 1.0f};	  // size of glyph
			JZEngine::Vec2f bearing_{0.0f, 0.0f}; // offset from baseline to left/top of glyph
			unsigned int advance{0};			  // horizontal offset to advance to next glyph
		};

		std::vector<std::map<char, Character>> font_characters_;
		// pre-compiles a list of characters from the given font
		void LoadFont(std::string font, unsigned int fontSize, const std::string &name, const std::string &vspath, const std::string &fspath);
		static std::vector<InstancedShaderID> instanced_shader_programs_;
		static std::vector<ShaderID> shader_programs_;
		static std::vector<DebugShader> debug_shaders_;
		//static std::vector<Texture2DID> texture2ds_;

		ResourceManager();

		virtual void PostInit() override;

		static unsigned int LoadInstancedShader(const std::string &name, const std::string &vspath, const std::string &fspath);
		static unsigned int LoadShader(const std::string &name, const std::string &vspath, const std::string &fspath);
		static unsigned int LoadDebugShader(const std::string &name, const std::string &vspath, const std::string &fspath);

		struct FolderData
		{
			std::string					path_;
			std::string					name_;
			std::vector<std::string>	files_;
			std::vector<FolderData>		folders_;
		};
		static FolderData texture_folder_data_;
		static std::unordered_map<std::string, std::vector<std::string>> texture_folders_;

		static unsigned int texture_unique_id_;
		static std::vector<Texture2DID> texture2ds_;
		static std::unordered_map<std::string, int> umap_texture2ds_;
		static void LoadAllTexturesInFolder(const std::string& folder = "Assets/Textures/");
		static void RecursivelyLoadTexture(const std::string& folder, FolderData& folderData);
		static Texture2D* GetTexture(int id);
		static Texture2D* GetTexture(const std::string& name);
		static int GetTextureID(const std::string& name);
	};
}