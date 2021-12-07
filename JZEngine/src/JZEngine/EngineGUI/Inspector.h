/*	__FILE HEADER__
*	File:		Inspector.h
	Primary:	Zachary Tay
	Secondary:	Jee Jia Min
	Date:		26/08/21
	Brief:		Renders all components of a selected entity
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
#include "../Resource/Serialize.h"

namespace JZEngine
{
	void PrintSystemAffected(std::string const& name);

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

		enum class VIEW
		{
			PROPERTY,
			SYSTEM,
			COMPONENT
		};

		VIEW view_ = VIEW::PROPERTY;

		bool component_view_{ true };
		
		bool		requesting_texture_{ false };
		std::string requested_texture_{ "" };


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

		void TreeNodeComponents ( ECS::Entity* const entity );

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

		static int TrimName ( const std::string& name );

		enum class Confirmation
		{
			NONE ,
			SERIALIZE
		};

		Confirmation confirmation_flag_{ Confirmation::NONE };
		char rename_buffer_[ 64 ] = { '\0' };
		void RenderConfirmation ( ECS::Entity* const entity );

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
			UNREFERENCED_PARAMETER ( component );
			ImGui::Text ( "Oops nothing here..." );
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

			// Child Position
			ImGui::Text ( "Relative Position" );
			ImGui::PushItemWidth ( ( w / 2.0f ) - spacing );
			ImGui::InputFloat ( "##RPosX" , &component.child_position_.x );
			ImGui::SameLine ();
			ImGui::Text ( "X" );
			ImGui::SameLine ();
			ImGui::InputFloat ( "##RPosY" , &component.child_position_.y );
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
			ImGui::Text ( "Size (cm)" );
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
				for( auto& texture : resource_manager_->umap_texture2ds_ )
				{
					if( ImGui::Selectable ( texture.first.c_str () ) )
					{
						component.texture_id_ = texture.second;
					}
				};
				ImGui::EndPopup ();
			};

			// button event to display all texture options
			// if no texture is found, meaning deleted, it will display as deleted
			std::string current_texture{ "Deleted" };
			for( auto& texture : resource_manager_->umap_texture2ds_ )
			{
				if( texture.second == component.texture_id_ )
				{
					current_texture = texture.first;
				}
			}
			if (ImGui::Button(current_texture.c_str(), ImVec2(168.0f, 0.0f)))
			{
				//ImGui::OpenPopup ( "Textures" );
				requesting_texture_ = true;
			}

			if (requested_texture_ != "")
			{
				current_texture = requested_texture_;
				component.texture_id_ = resource_manager_->umap_texture2ds_[current_texture];
				requested_texture_ = "";
			}

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
			// Making of color pallette starts here .
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

			ImVec4 temp_color = { component.tint.x, component.tint.y, component.tint.z, component.tint.w };

			// Generate a default palette. The palette will persist and can be edited.
			static bool saved_palette_init = true;
			// Palette are divided by 4 rows and 8 column
			static ImVec4 saved_palette[ 32 ] = {};
			if( saved_palette_init )
			{
				for( int n = 0; n < IM_ARRAYSIZE ( saved_palette ); n++ )
				{
					ImGui::ColorConvertHSVtoRGB ( n / 31.0f , 0.8f , 0.8f ,
												  saved_palette[ n ].x , saved_palette[ n ].y , saved_palette[ n ].z );
					// Default alpha ( we will do changeable alpha soon !)
					saved_palette[ n ].w = temp_color.w; // Alpha
				}
				saved_palette_init = false;
			}


			static ImVec4 backup_color;
			bool open_popup = ImGui::ColorButton ( "MyColor##3b" , temp_color );

			ImGui::SameLine ( 0 , ImGui::GetStyle ().ItemInnerSpacing.x );
			open_popup |= ImGui::Button ( "Palette" );
			if( open_popup )
			{
				ImGui::OpenPopup ( "mypicker" );
				backup_color = temp_color;
			}
			if( ImGui::BeginPopup ( "mypicker" ) )
			{
				ImGui::Text ( "CUSTOM COLOR PALETTE!" );
				ImGui::Separator ();
				ImGui::ColorPicker4 ( "##picker" , ( float* ) &temp_color , ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview );
				ImGui::SameLine ();

				ImGui::BeginGroup (); // Lock X position
				ImGui::Text ( "Current" );
				ImGui::ColorButton ( "##current" , temp_color , ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf , ImVec2 ( 60 , 40 ) );
				ImGui::Text ( "Previous" );
				if( ImGui::ColorButton ( "##previous" , backup_color , ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf , ImVec2 ( 60 , 40 ) ) )
					temp_color = backup_color;
				ImGui::Separator ();
				ImGui::Text ( "Palette" );
				for( int n = 0; n < IM_ARRAYSIZE ( saved_palette ); n++ )
				{
					ImGui::PushID ( n );
					if( ( n % 8 ) != 0 )
						ImGui::SameLine ( 0.0f , ImGui::GetStyle ().ItemSpacing.y );

					ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
					if( ImGui::ColorButton ( "##palette" , saved_palette[ n ] , palette_button_flags , ImVec2 ( 20 , 20 ) ) )
						//temp_color = ImVec4 ( saved_palette[ n ].x , saved_palette[ n ].y , saved_palette[ n ].z , temp_color.w ); // Preserve alpha!

						temp_color = ImVec4 ( saved_palette[ n ].x , saved_palette[ n ].y , saved_palette[ n ].z , saved_palette[ n ].w ); // Preserve alpha!

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
			component.tint = { temp_color.x, temp_color.y, temp_color.z , temp_color.w };
			//  End of color pallette making !
			////////////////////////////////////////////////////////////
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
		void RenderComponent ( CollisionComponent& component )
		{
			// General data
			ImGuiStyle& style = ImGui::GetStyle ();
			float w = ImGui::CalcItemWidth ();
			float spacing = style.ItemInnerSpacing.x;

			ImGui::Text ( "Shape" );

			ImGui::SliderInt ( "ID" , &component.shapeid , 0 , 1 );

			ImGui::Text ( "Offset" );
			ImGui::PushItemWidth ( ( w / 2.0f ) - ( spacing * 3.0f ) );
			ImGui::InputFloat ( "##OffSetX" , &component.offset.x );
			ImGui::SameLine ();
			ImGui::Text ( "X" );
			ImGui::SameLine ();
			ImGui::InputFloat ( "##OffSetY" , &component.offset.y );
			ImGui::SameLine ();
			ImGui::Text ( "Y" );
			ImGui::PopItemWidth ();

			ImGui::Text ( "Collision Size (cm)" );
			ImGui::PushItemWidth ( ( w / 3.0f ) - spacing );
			ImGui::InputFloat ( "##SizeW" , &component.size.x );
			ImGui::SameLine ();
			ImGui::Text ( "X or Radius" );

			ImGui::InputFloat ( "##SizeY" , &component.size.y );
			ImGui::SameLine ();
			ImGui::Text ( "Y" );
			ImGui::PopItemWidth ();
		}
		template <>
		void RenderComponent ( PhysicsComponent& component )
		{
			// General data
			ImGuiStyle& style = ImGui::GetStyle ();
			float w = ImGui::CalcItemWidth ();
			float spacing = style.ItemInnerSpacing.x;



			ImGui::Checkbox ( "Static" , &component.IsStatic );
			ImGui::Checkbox ( "Player" , &component.player );

			ImGui::Text ( "Velocity (cm/s)" );
			ImGui::PushItemWidth ( ( w / 2.0f ) - ( spacing * 3.0f ) );
			ImGui::InputFloat ( "##VelX" , &component.velocity.x );
			ImGui::SameLine ();
			ImGui::Text ( "X" );
			ImGui::SameLine ();
			ImGui::InputFloat ( "##VelY" , &component.velocity.y );
			ImGui::SameLine ();
			ImGui::Text ( "Y" );
			ImGui::PopItemWidth ();

			ImGui::Text ( "Angular Velocity (degree/s)" );
			ImGui::PushItemWidth ( ( w / 2.0f ) - ( spacing * 3.0f ) );
			ImGui::InputFloat ( "##Vel" , &component.angularVelocity );
			ImGui::SameLine ();
			ImGui::Text ( "o" );
			ImGui::PopItemWidth ();

			ImGui::Text ( "Area" );
			ImGui::SliderFloat ( "cm^2" , &component.Area , component.Area , component.Area );
			ImGui::Text ( "Density " );
			ImGui::SliderFloat ( "kg/cm^2" , &component.Density , 0.001f , 1.f );
			ImGui::Text ( "Mass" );
			ImGui::SliderFloat ( "kg" , &component.Mass , component.Mass - 10.0f , component.Mass + 10.0f );
			ImGui::Text ( "Restitution (Bounciness)" );
			ImGui::SliderFloat ( "##PhysicsComponentRestitution" , &component.Restitution , 0.0f , 1.0f );

			ImGui::Text ( "Static Friction" );
			ImGui::SliderFloat ( "##PhysicsComponentStaticFriction" , &component.StaticFriction , 0.0f , 1.5f );

			ImGui::Text ( "Dynamic Friction" );
			ImGui::SliderFloat ( "##PhysicsComponentDynamicFriction" , &component.DynamicFriction , 0.0f , 1.5f );

			ImGui::Text("Add Force");
			ImGui::PushItemWidth((w / 2.0f) - (spacing * 3.0f));
			ImGui::InputFloat("##X", &component.externalforce.x);
			ImGui::SameLine();
			ImGui::Text("X");
			ImGui::SameLine();
			ImGui::InputFloat("##Y", &component.externalforce.y);
			ImGui::SameLine();
			ImGui::Text("Y");
			ImGui::PopItemWidth();
		}

		template <>
		void RenderComponent ( Parallax& component )
		{
			std::string items [] = { "X", "Y" };
			static std::string current_item = items[ 0 ] ;

			ImGuiStyle& style = ImGui::GetStyle ();
			float w = ImGui::CalcItemWidth ();
			float spacing = style.ItemInnerSpacing.x;
			//float button_sz = ImGui::GetFrameHeight ();
			ImGui::PushItemWidth ( ( w / 2.0f ) - spacing );

			if( ImGui::BeginCombo ( "##custom combo" , current_item.c_str () , ImGuiComboFlags_NoArrowButton ) )
			{
				for( int n = 0; n < IM_ARRAYSIZE ( items ); n++ )
				{
					bool is_selected = ( current_item == items[ n ] );
					if( ImGui::Selectable ( items[ n ].c_str () , is_selected ) )
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

		template <>
		void RenderComponent ( TextData& component )
		{
			// General data
			ImGuiStyle& style = ImGui::GetStyle ();
			float w = ImGui::CalcItemWidth ();
			float spacing = style.ItemInnerSpacing.x;

			// Font Size
			ImGui::Text ( "Font Size" );
			ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
			ImGui::InputFloat ( "##fontscale" , &component.font_size_ , 0.0f , 100.0f );

			// Font Tracking
			ImGui::Text ( "Tracking" );
			ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
			ImGui::InputFloat ( "##fonttracking" , &component.tracking_x_ , 1.0f , 10.0f );

			// Font Leading 
			ImGui::Text ( "Leading" );
			ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
			ImGui::InputFloat ( "##fontleading" , &component.leading_y_ , 1.0f , 10.0f );

			const char* font_memo
			{
				"ENTER to type on new line.\n"
				"Maximum of 199 characters."
				"! Alpha is not integrated at this moment.\n"
				"Thank you for your patience !"
			};

			// Input Text
			ImGui::Text ( "Text" );
			ImGui::SameLine ();
			ImGui::TextDisabled ( "(?)" );
			if( ImGui::IsItemHovered () )
			{
				ImGui::BeginTooltip ();
				ImGui::PushTextWrapPos ( ImGui::GetFontSize () * 35.0f );
				ImGui::TextUnformatted ( font_memo );
				ImGui::PopTextWrapPos ();
				ImGui::EndTooltip ();
			}
			static ImGuiInputTextFlags flags ;
			ImGui::InputTextMultiline ( "##fonttext" , component.text.data , IM_ARRAYSIZE ( component.text.data ) , ImVec2 ( w + ( spacing * 4.0f ) , ImGui::GetTextLineHeight () * 10 ) , flags );
			ImGui::CheckboxFlags ( "Lock " , &flags , ImGuiInputTextFlags_ReadOnly );
			ImGui::SameLine ( 0 , ( spacing * 4.0f ) );
			ImGui::Text ( "Characters " );
			ImGui::SameLine ( 0 , spacing );
			ImGui::Text ( "%d " , component.text.size () );

			// Text color
			static float color[ 3 ];
			ImGui::ColorEdit3 ( "Color" , color );
			component.color_.x = color[ 0 ];
			component.color_.y = color[ 1 ];
			component.color_.z = color[ 2 ];


		}

		template <>
		void RenderComponent ( Animation2D& component )
		{
			ImGui::Checkbox ( "Animation" , &component.animation_check_ );
			if( component.animation_check_ )
			{
				// General data
				ImGuiStyle& style = ImGui::GetStyle ();
				float w = ImGui::CalcItemWidth ();
				float spacing = style.ItemInnerSpacing.x;

				// No. of frame it is currently at.
				ImGui::Text ( "Current Frame" );
				ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
				ImGui::SliderInt ( "##AnimationFrame" , &component.frame_ , 0 , component.max_frames_ - 1 );

				ImGui::Text ( "Max Frames" );
				ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
				ImGui::SliderInt ( "##AnimationMaxFrames" , &component.max_frames_ , 1 , component.rows_ * component.column_ );

				ImGui::Text ( "Frame Speed" );
				ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
				if( component.animation_speed_ >= 2.0f )
				{
					component.animation_speed_ = 2.0f;
				}
				else if( component.animation_speed_ <= 0.0f )
				{
					component.animation_speed_ = 0.0f;
				}
				ImGui::InputFloat ( "##AnimationFrameSpeed" , &component.animation_speed_ , 0.1f , 2.0f , "%.2f" );

				ImGui::Text ( "Rows" );
				ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
				ImGui::SliderInt ( "##AnimationRows" , &component.rows_ , 1 , 100 );

				ImGui::Text ( "Columns" );
				ImGui::SetNextItemWidth ( w + ( spacing * 4.0f ) );
				ImGui::SliderInt ( "##AnimationColumns" , &component.column_ , 1 , 100 );
			}
		}

		template <>
		void RenderComponent ( SpriteLayer& component )
		{
			ImGui::InputInt ( ": Layer" , &component.layer_ );
		}

		template <>
		void RenderComponent ( MouseEvent& component )
		{
			ImGui::InputFloat ( "##MEX" , &component.bounding_half_width_ );
			ImGui::InputFloat ( "##MEY" , &component.bounding_half_height_ );
		}

		int current_id = 0;
		template<>
		void RenderComponent ( CustomLogicContainer& component )
		{
			// display selection for all the functions
			if ( ImGui::BeginPopup ( "Updates" ) )
			{
				if ( ImGui::Selectable ( "Remove" ) )
				{
					component.updates[ current_id ] = 0;
				}
				for ( auto& update : LogicContainer::Instance ().GetUpdates () )
				{
					if ( update.first != "Remove" )
					{
						if ( ImGui::Selectable ( update.first.c_str () ) )
						{
							component.updates[ current_id ] = update.second;
						}
					}
				};
				ImGui::EndPopup ();
			};

			int next_slot = -1;
			float button_width = ImGui::GetWindowWidth () * 0.8f;
			for ( int i = 0; i < MAX_LOGIC_PER_ENTITY; ++i )
			{
				if ( component.updates[ i ] != 0 )
				{
					if ( ImGui::Button ( LogicContainer::Instance ().GetUpdateName ( component.updates[ i ] ).c_str () , { button_width, 0 } ) )
					{
						current_id = i;
						ImGui::OpenPopup ( "Updates" );
					}
				}
				else
				{
					next_slot = i;
				}
			}
			if ( next_slot != -1 )
			{
				if ( ImGui::Button ( "- Select -" , { button_width, 0 } ) )
				{
					current_id = next_slot;
					ImGui::OpenPopup ( "Updates" );
				}
			}
			else
			{
				ImGui::Text ( "Max functions stored." );
			}
		}

		struct TestType
		{
			int a , b;
		};

		template<>
		void RenderComponent ( CustomDataContainer& component )
		{
			ImGui::Text ( "Unable to display custom data." );
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
			UNREFERENCED_PARAMETER ( t );
			UNREFERENCED_PARAMETER ( i );
			UNREFERENCED_PARAMETER ( entity );
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
					ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 45.0f);
					if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("deleteicon")->GetRendererID()), { 15.0f, 15.0f }, { 0,1 }, { 1,0 }))
					{
						entity.RemoveComponent(i);
					}
					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text("Remove this component.");
						ImGui::Separator();
						ImGui::Text("These systems will no longer update this entity:");
						ImGui::Separator();
						ImGui::NewLine();

						ECS::ECSConfig::System systems;
						std::apply([&i, &entity](auto&...systems) { (systems.NotifyInspectorMissingComponent(i, PrintSystemAffected, entity.owning_chunk_->owning_archetype_->mask_), ...); }, systems);

						ImGui::EndTooltip();
					}
					ImGui::TreePop ();
				}
				return;
			}
			LoopTupleRender<I + 1> ( t , i , entity );
		}
	};
}