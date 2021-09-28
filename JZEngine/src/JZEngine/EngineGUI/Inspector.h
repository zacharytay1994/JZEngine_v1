/*	__FILE HEADER__
*	File:	Inspector.h
	Author: JZ
	Date:	26/08/21
	Brief:	Renders all components of a selected entity
			in the engine GUI with ImGui.
*/

#pragma once

#include <tuple>
#include <string>

#include "../BuildDefinitions.h"
#include "../ImGui/imgui.h"

#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

#include "../Resource/ResourceManager.h"

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::Inspector___
	 * ****************************************************************************************************
	 * Renders the components of a selected entity.
	 * Able to add and remove entities from the selected entity.
	 * ****************************************************************************************************
	*/
	struct JZENGINE_API Inspector
	{
		ECS::ECSInstance* ecs_instance_{ nullptr };
		ResourceManager* resource_manager_{ nullptr };
		float x_ , y_ , sx_ , sy_;		/*!< position and scale of the ImGui window */

		Inspector ( float x , float y , float sx , float sy );

		/*!
		 * @brief ___JZEngine::ToolsGUI::RenderInspector()___
		 * ****************************************************************************************************
		 * ImGUI window for the inspector, entity details.
		 * ****************************************************************************************************
		 * @param entity
		 * : The entity of which to display the details.
		 * ****************************************************************************************************
		*/
		void Render ( ECS::Entity* const entity = nullptr );

		/*!
		 * @brief ___JZEngine::ToolsGUI::TreeNodeComponentAndSystems()___
		 * ****************************************************************************************************
		 * Creates an ImGUI tree node of all registered
		 * components and systems in the engine. Called
		 * in RenderInspector. It is part of the inspector
		 * display.
		 * ****************************************************************************************************
		*/
		void TreeNodeComponentsAndSystems ( ECS::Entity* const entity );

		int TrimName ( const std::string& name );

		/* ____________________________________________________________________________________________________
		*	CUSTOM COMPONENT IMGUI LAYOUTS
		   ____________________________________________________________________________________________________*/

		   /*!
			* @brief ___JZEngine::Inspector::RenderComponent()___
			* ****************************************************************************************************
			* Default template for a component to be rendered using ImGui.
			* ****************************************************************************************************
			* @tparam COMPONENT
			* : Specialization to choose a function.
			* @param component
			* : The component reference to inspect component values from.
			* ****************************************************************************************************
		   */
		template <typename COMPONENT>
		void RenderComponent ( COMPONENT& component )
		{
			ImGui::Text ( "Oops nothing here..." );
		}

		template <>
		void RenderComponent ( TestComponent& component )
		{
			ImGui::SliderInt ( "x" , &component.x , -180 , 180 );
			ImGui::SliderInt ( "y" , &component.y , -180 , 180 );
		}

		template <>
		void RenderComponent ( Transform& component )
		{
			// General data
			ImGuiStyle& style = ImGui::GetStyle ();
			float w = ImGui::CalcItemWidth ();
			float spacing = style.ItemInnerSpacing.x;
			float button_sz = ImGui::GetFrameHeight ();

			// Position
			ImGui::Text ( "Position" );
			ImGui::PushItemWidth ( ( w / 2.0f ) - spacing );
			ImGui::InputFloat ( "##PosX" , &component.position_.x );
			ImGui::SameLine ();
			ImGui::Text ( "X" );
			ImGui::SameLine ();
			ImGui::InputFloat ( "##PosY" , &component.position_.y );
			ImGui::SameLine ();
			ImGui::Text ( "Y" );
			ImGui::PopItemWidth ();

			// Rotation
			ImGui::Text ( "Rotation" );
			ImGui::PushItemWidth ( w - ( button_sz * 2.0f ) + ( spacing * 2.0f ) );
			ImGui::SliderFloat ( "##rotateslide" , &component.rotation_ , -360.0f , 360.0f );
			ImGui::PopItemWidth ();
			ImGui::SameLine ( 0 , spacing );
			if( ImGui::ArrowButton ( "##rotateleft" , ImGuiDir_Left ) )
			{
				if( ( component.rotation_ < 360.0f ) && ( component.rotation_ > -360.0f ) )
				{
					component.rotation_ -= 1.0f;
				}
			}
			ImGui::SameLine ( 0 , spacing );
			if( ImGui::ArrowButton ( "##rotateright" , ImGuiDir_Right ) )
			{
				if( ( component.rotation_ < 360.0f ) && ( component.rotation_ > -360.0f ) )
				{
					component.rotation_ += 1.0f;
				}
			}
			ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
			ImGui::InputFloat ( "##rotateinput" , &component.rotation_ , -360.0f , 360.0f );
			ImGui::SameLine ();
			ImGui::Text ( "R" );

			// Scale
			ImGui::Text ( "Scale" );
			ImGui::PushItemWidth ( ( w / 2.0f ) - spacing );
			ImGui::InputFloat ( "##ScaleX" , &component.scale_.x );
			ImGui::SameLine ();
			ImGui::Text ( "X" );
			ImGui::SameLine ();
			ImGui::InputFloat ( "##ScaleY" , &component.scale_.y );
			ImGui::SameLine ();
			ImGui::Text ( "Y" );
			ImGui::PopItemWidth ();

			// Size
			ImGui::Text ( "Size" );
			ImGui::PushItemWidth ( ( w / 2.0f ) - spacing );
			ImGui::InputFloat ( "##SizeW" , &component.size_.x );
			ImGui::SameLine ();
			ImGui::Text ( "W" );
			ImGui::SameLine ();
			ImGui::InputFloat ( "##SizeH" , &component.size_.y );
			ImGui::SameLine ();
			ImGui::Text ( "H" );
			ImGui::PopItemWidth ();
		}

		template <>
		void RenderComponent ( Texture& component )
		{
			// display selection for all the textures
			if( ImGui::BeginPopup ( "Textures" ) )
			{
				for( auto& texture : resource_manager_->texture2ds_ )
				{
					if( ImGui::Selectable ( texture.name_.c_str () ) )
					{
						component.texture_id_ = texture.id_;
					}
				}
				ImGui::EndPopup ();
			}

			// button event to display all texture options
			if( ImGui::Button ( resource_manager_->texture2ds_[ component.texture_id_ ].name_.c_str () , ImVec2 ( 168.0f , 0.0f ) ) )
				ImGui::OpenPopup ( "Textures" );

			ImGui::SameLine ();
			ImGui::Text ( "Texture" );
		}

		template <>
		void RenderComponent ( NonInstanceShader& component )
		{
			// display selection for all the shaders
			if( ImGui::BeginPopup ( "Shaders" ) )
			{
				for( auto& shader : resource_manager_->shader_programs_ )
				{
					if( ImGui::Selectable ( shader.name_.c_str () ) )
					{
						component.shader_id_ = shader.id_;
					}
				}
				ImGui::EndPopup ();
			}

			// button event to display all shaders options
			if( ImGui::Button ( resource_manager_->shader_programs_[ component.shader_id_ ].name_.c_str () , ImVec2 ( 168.0f , 0.0f ) ) )
				ImGui::OpenPopup ( "Shaders" );

			ImGui::SameLine ();
			ImGui::Text ( "Shader" );

			////////////////////////////////////////////////////////////
			static ImVec4 color{};
			const char* memo
			{
				"Click on the color square to open a color picker.\n"
				"Click and hold to use drag and drop.\n"
				"Right-click on the color square to show options.\n"
				"CTRL+click on individual component to input value.\n"
			};

			ImGui::Text ( "Tint" );

			ImGui::SameLine ();
			ImGui::TextDisabled ( "(?)" );
			if( ImGui::IsItemHovered () )
			{
				ImGui::BeginTooltip ();
				ImGui::PushTextWrapPos ( ImGui::GetFontSize () * 35.0f );
				ImGui::TextUnformatted ( memo );
				ImGui::PopTextWrapPos ();
				ImGui::EndTooltip ();
			}

			// Generate a default palette. The palette will persist and can be edited.
			static bool saved_palette_init = true;
			static ImVec4 saved_palette[ 32 ] = {};
			if( saved_palette_init )
			{
				for( int n = 0; n < IM_ARRAYSIZE ( saved_palette ); n++ )
				{
					ImGui::ColorConvertHSVtoRGB ( n / 31.0f , 0.8f , 0.8f ,
												  saved_palette[ n ].x , saved_palette[ n ].y , saved_palette[ n ].z );
					saved_palette[ n ].w = 1.0f; // Alpha
				}
				saved_palette_init = false;
			}

			component.tint.x = 1.0f * color.x ;
			component.tint.y = 1.0f * color.y ;
			component.tint.z = 1.0f * color.z ; 

			static ImVec4 backup_color;
			bool open_popup = ImGui::ColorButton ( "MyColor##3b" , color );
			ImGui::SameLine ( 0 , ImGui::GetStyle ().ItemInnerSpacing.x );
			open_popup |= ImGui::Button ( "Palette" );
			if( open_popup )
			{
				ImGui::OpenPopup ( "mypicker" );
				backup_color = color;
			}
			if( ImGui::BeginPopup ( "mypicker" ) )
			{
				ImGui::Text ( "CUSTOM COLOR PALETTE!" );
				ImGui::Separator ();
				ImGui::ColorPicker4 ( "##picker" , ( float* ) &color , ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview );
				ImGui::SameLine ();

				ImGui::BeginGroup (); // Lock X position
				ImGui::Text ( "Current" );
				ImGui::ColorButton ( "##current" , color , ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf , ImVec2 ( 60 , 40 ) );
				ImGui::Text ( "Previous" );
				if( ImGui::ColorButton ( "##previous" , backup_color , ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf , ImVec2 ( 60 , 40 ) ) )
					color = backup_color;
				ImGui::Separator ();
				ImGui::Text ( "Palette" );
				for( int n = 0; n < IM_ARRAYSIZE ( saved_palette ); n++ )
				{
					ImGui::PushID ( n );
					if( ( n % 8 ) != 0 )
						ImGui::SameLine ( 0.0f , ImGui::GetStyle ().ItemSpacing.y );

					ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
					if( ImGui::ColorButton ( "##palette" , saved_palette[ n ] , palette_button_flags , ImVec2 ( 20 , 20 ) ) )
						color = ImVec4 ( saved_palette[ n ].x , saved_palette[ n ].y , saved_palette[ n ].z , color.w ); // Preserve alpha!

					// Allow user to drop colors into each palette entry. Note that ColorButton() is already a
					// drag source by default, unless specifying the ImGuiColorEditFlags_NoDragDrop flag.
					if( ImGui::BeginDragDropTarget () )
					{
						if( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload ( IMGUI_PAYLOAD_TYPE_COLOR_3F ) )
							memcpy ( ( float* ) &saved_palette[ n ] , payload->Data , sizeof ( float ) * 3 );
						if( const ImGuiPayload* payload = ImGui::AcceptDragDropPayload ( IMGUI_PAYLOAD_TYPE_COLOR_4F ) )
							memcpy ( ( float* ) &saved_palette[ n ] , payload->Data , sizeof ( float ) * 4 );
						ImGui::EndDragDropTarget ();
					}
					ImGui::PopID ();
				}
				ImGui::EndGroup ();
				ImGui::EndPopup ();
			}
		}

		template <>
		void RenderComponent ( InstanceShader& component )
		{
			// display selection for all the shaders
			if( ImGui::BeginPopup ( "Shaders" ) )
			{
				for( auto& shader : resource_manager_->instanced_shader_programs_ )
				{
					if( ImGui::Selectable ( shader.name_.c_str () ) )
					{
						component.shader_id_ = shader.id_;
					}
				}
				ImGui::EndPopup ();
			}

			// button event to display all shaders options
			if( ImGui::Button ( resource_manager_->instanced_shader_programs_[ component.shader_id_ ].name_.c_str () , ImVec2 ( 168.0f , 0.0f ) ) )
				ImGui::OpenPopup ( "Shaders" );

			ImGui::SameLine ();
			ImGui::Text ( "Shader" );
		}

		template <>
		void RenderComponent ( MyNewComponent& component )
		{
			ImGui::SliderInt ( "x" , &component.not_a_component.im_another_component_.x , -3000 , 1000 );
			ImGui::SliderInt ( "y" , &component.not_a_component.im_another_component_.y , -2000 , 1000 );
			ImGui::SliderFloat ( "a float" , &component.not_a_component.im_a_float_ , -300 , 300 );
			ImGui::Text ( "this is a %c" , component.nomal_data_ );
		}
		template <>
		void RenderComponent ( IsInputAffected& component )
		{
			ImGui::SliderFloat ( "val" , &component.val , -2.0f , 2.0f );
		}

		template <>
		void RenderComponent ( PhysicsComponent& component )
		{
			ImGui::SliderInt ( "Shape" , &component.shapeid , 0 , 1 );
			ImGui::SliderFloat ( "Velocity of y" , &component.velocity.y , component.velocity.y - 0.1f , component.velocity.y + 0.1f );
		}

		template <>
		void RenderComponent ( Parallax& component )
		{
			const char* items [] = { "X", "Y" };
			static const char* current_item = items[ 0 ] ;

			ImGuiStyle& style = ImGui::GetStyle ();
			float w = ImGui::CalcItemWidth ();
			float spacing = style.ItemInnerSpacing.x;
			float button_sz = ImGui::GetFrameHeight ();
			ImGui::PushItemWidth ( ( w / 2.0f ) - spacing );

			if( ImGui::BeginCombo ( "##custom combo" , current_item , ImGuiComboFlags_NoArrowButton ) )
			{
				for( int n = 0; n < IM_ARRAYSIZE ( items ); n++ )
				{
					bool is_selected = ( current_item == items[ n ] );
					if( ImGui::Selectable ( items[ n ] , is_selected ) )
						current_item = items[ n ];
					if( is_selected )
						ImGui::SetItemDefaultFocus ();
				}
				ImGui::EndCombo ();
			}
			ImGui::PopItemWidth ();
			ImGui::SameLine ( 0 , spacing );
			ImGui::PushItemWidth ( ( w / 2.0f ) - spacing );
			// X axis = Horizontal
			if( current_item == "X" )
			{
				component.is_vertical = false ;
				component.speed_y_ = 0.0f;
				ImGui::InputFloat ( "##x" , &component.speed_x_ );
			}
			// Y axis = Vertical
			if( current_item == "Y" )
			{
				component.is_vertical = true;
				component.speed_x_ = 0.0f;
				ImGui::InputFloat ( "##y" , &component.speed_y_ );
			}
			ImGui::PopItemWidth ();
		}

		/*!
		 * @brief ___JZEngine::LoopTupleRender___
		 * ****************************************************************************************************
		 * Loops through a ECS::ECSConfig::Component to get a
		 * Component type to call the template specialization
		 * defined above.
		 * ****************************************************************************************************
		 * @param i
		 * : The index of the Component type into the tuple.
		 * @param entity
		 * : The entity to get the component from.
		 * ****************************************************************************************************
		*/
		template <size_t I = 0 , typename...TUPLE>
		typename std::enable_if<I == sizeof...( TUPLE ) , void>::type
			LoopTupleRender ( std::tuple<TUPLE...> t , size_t i , ECS::Entity& entity )
		{
			std::cout << "LoopTupleRender::tuple size exceeded." << std::endl;
			return;
		}

		template <size_t I = 0 , typename...TUPLE>
		typename std::enable_if < I < sizeof...( TUPLE ) , void>::type
			LoopTupleRender ( std::tuple<TUPLE...> t , size_t i , ECS::Entity& entity )
		{
			if( I == i )
			{
				using COMPONENT = decltype( std::get<I> ( t ) );
				if( ImGui::TreeNodeEx ( typeid( COMPONENT ).name () , ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Framed ) )
				{
					RenderComponent ( entity.GetComponent<std::remove_reference_t<COMPONENT>> () );
					ImGui::TreePop ();
				}
				return;
			}
			LoopTupleRender<I + 1> ( t , i , entity );
		}
	};
}