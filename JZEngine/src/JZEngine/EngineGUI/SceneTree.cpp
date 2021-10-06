/*	__FILE HEADER__
*	File:	SceneTree.cpp
	Author: JZ
	Date:	26/08/21
	Brief:	Renders all entities in the scene tree on the
			GUI using ImGui.
*/

#include "PCH.h"
#include "SceneTree.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "Console.h"
#include "../Resource/Serialize.h"
#include "MenuBar.h"

namespace JZEngine
{
	SceneTree::SceneTree ( float x , float y , float sx , float sy )
		:
		x_ ( x ) , y_ ( y ) , sx_ ( sx ) , sy_ ( sy )
	{
		default_entity_name_ = new std::string("NoName");
		//*default_entity_name_ = "Entity";
		names_ = new std::unordered_map<std::string, unsigned int>();
		current_scene_name_ = new std::string("New Scene");
		new_entity_name_[0] = '\0';
	}

	SceneTree::~SceneTree ()
	{
		delete default_entity_name_;
		delete names_;
		delete current_scene_name_;
	}

	/*!
	 * @brief ___JZEngine::SceneTree::Render()___
	 * ****************************************************************************************************
	 * Renders the ImGui window.
	 * ****************************************************************************************************
	*/
	void SceneTree::Render ()
	{
		ImGui::SetNextWindowBgAlpha ( 1.0f );
		ImGui::SetNextWindowPos ( { static_cast< float >( Settings::window_width ) * x_, MenuBar::height_ } , ImGuiCond_Always );
		ImGui::SetNextWindowSize ( { static_cast< float >( Settings::window_width ) * sx_, static_cast<float>(Settings::window_height - MenuBar::height_) } , ImGuiCond_Always );
		ImGui::Begin ( "Scene Heirarchy" , 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

		ImGui::Text("%s", current_scene_name_->c_str());
		ImGui::Separator();
		if (ImGui::Button("Save"))
		{
			confirmation_flag_ = Confirmation::SAVE;
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove All"))
		{
			RemoveAllEntities();
		}
		ImGui::Separator();
		// render text box for input name
		ImGui::InputText ( ": Name" , new_entity_name_ , MAX_NAME_SIZE );

		if( ImGui::Button ( "Add Default Entity" ) )
		{
			// create a new entity, pushed into EntityManager
			unsigned int id = ecs_instance_->CreateEntity ();

			// if successful
			if( id != -1 )
			{
				// rename it
				ecs_instance_->GetEntity ( id ).name_ = GetName ();
			}
		}
		ImGui::Text ( "\nCurrent Scene" );

		static ImGuiTextFilter filter;
		// Helper class to easy setup a text filter.
		// You may want to implement a more feature-full filtering scheme in your own application.
		filter.Draw ( ": Filter" );

		ImGui::PushStyleColor ( ImGuiCol_Separator , { 0.8f,0.8f,0.8f,1.0f } );
		ImGui::Separator ();
		ImGui::PopStyleColor ();

		int popup_id{ 0 };
		// render all root entities in EntityManager
		for( auto& id : ecs_instance_->entity_manager_.root_ids_ )
		{
			if( id != -1 )
			{
				ECS::Entity* e = &ecs_instance_->entity_manager_.GetEntity ( id );
				if( filter.PassFilter ( e->name_.c_str () ) )
				{
					RenderAllChildObjects ( e, ++popup_id );
				}
				// recursively render all children of a root entity
				//RenderAllChildObjects(&ecs_instance_->entity_manager_.GetEntity(id), ++popup_id);
			}
		}
		ImGui::End();

		if (confirmation_flag_ != Confirmation::NONE) {
			RenderConfirmation();
		}
	}

	/*!
	 * @brief ___JZEngine::SceneTree::RenderAllChildObjects()___
	 * ****************************************************************************************************
	 * Recursive function that renders the entity in the tree,
	 * and also all of its children under it.
	 * ****************************************************************************************************
	 * @param entity
	 * : The entity to render. Should be a root entity in EntityManager.
	 * ****************************************************************************************************
	*/
	void SceneTree::RenderAllChildObjects(ECS::Entity* entity, int& id)
	{
		std::stringstream ss;
		ss << entity->name_;

		// add own tree node
		ImGui::SetNextItemOpen ( true , ImGuiCond_Once );
		bool is_selected = false;
		if( selected_entity_ )
		{
			if( entity->entity_id_ == selected_entity_->entity_id_ )
			{
				is_selected = true;
				ImGui::PushStyleColor ( ImGuiCol_Text , { 0.0f,1.0f,0.0f,1.0f } );
			}
		}

		bool open = ImGui::TreeNodeEx ( ss.str ().c_str () , ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick );

		// if a treenode is clicked, make that entity the selected_entity_
		if( ImGui::IsItemClicked () )
		{
			selected_entity_ = entity;
		}
		std::stringstream unique_popup_id_;
		unique_popup_id_ << id;
		if (ImGui::BeginPopupContextItem(unique_popup_id_.str().c_str()))
		{
			// adds an entity as a child of this entity on right click
			if( ImGui::Selectable ( "Add Entity" ) )
			{
				int id = ecs_instance_->CreateEntity ( entity->entity_id_ );
				if( id == -1 )
				{
					std::stringstream ss;
					ss << "Entity " << entity->name_ << " (ID: " << entity->entity_id_ << ") has maximum number of children!";
					//Console::Log(ss.str().c_str());
				}
				else
				{
					ECS::Entity& created_entity = ecs_instance_->GetEntity ( id );
					created_entity.name_ = GetName ();
				}
			}
			// removes an entity from the tree
			if( ImGui::Selectable ( "Remove Entity" ) )
			{
				ecs_instance_->RemoveEntity ( entity->entity_id_ );
				selected_entity_ = nullptr;
			}
			if (ImGui::Selectable("Rename"))
			{
				if (new_entity_name_[0] != '\0')
				{

					entity->name_ = new_entity_name_;
				}
			}

			ImGui::EndPopup();
		}
		if( is_selected )
		{
			ImGui::PopStyleColor ();
		}

		// end own tree node
		if( open )
		{
			// add all child tree nodes
			for( auto& c : entity->children_ )
			{
				if( c != -1 )
				{
					RenderAllChildObjects(&ecs_instance_->entity_manager_.GetEntity(c), ++id);
				}
			}
			ImGui::TreePop ();
		}
	}

	/*!
	 * @brief ___JZEngine::SceneTree::GetName()___
	 * ****************************************************************************************************
	 * Gets a unique name in the scene. If a name
	 * is repeated, pad it with an index.
	 * ****************************************************************************************************
	 * @return std::string
	 * : The name padded with the index.
	 * ****************************************************************************************************
	*/
	std::string SceneTree::GetName ()
	{
		// if a custom name is typed
		if( new_entity_name_[ 0 ] == '\0' )
		{
			std::stringstream ss;
			ss << *default_entity_name_;

			// pad identical names with an index
			if( names_->find ( *default_entity_name_ ) == names_->end () )
			{
				( *names_ )[ *default_entity_name_ ] = 1;
				return *default_entity_name_;
			}
			else
			{
				ss << "(" << ( *names_ )[ *default_entity_name_ ]++ << ")";
				return ss.str ();
			}
		}
		// else use the default name padded with index
		else
		{
			std::stringstream ss;
			ss << new_entity_name_;
			if( names_->find ( new_entity_name_ ) == names_->end () )
			{
				( *names_ )[ new_entity_name_ ] = 1;
				return ss.str ();
			}
			else
			{
				ss << "(" << ( *names_ )[ new_entity_name_ ]++ << ")";
				return ss.str ();
			}
		}
	}

	void SceneTree::RemoveAllEntities()
	{
		// remove all root entities which also removes all children
		for (int i = ecs_instance_->entity_manager_.root_ids_.size() - 1; i >= 0; --i)
		{
			if (ecs_instance_->entity_manager_.root_ids_[i] != -1)
			{
				ecs_instance_->RemoveEntity(ecs_instance_->entity_manager_.root_ids_[i]);
			}
		}
		for (auto& name : *names_)
		{
			name.second = 0;
		}
		*current_scene_name_ = "New Scene";
	}

	template <typename... ARGS>
	void TextCenter(std::string text, ARGS...args) {
		float font_size = ImGui::GetFontSize() * text.size() / 2;
		ImGui::SameLine(
			ImGui::GetWindowSize().x / 2 -
			font_size + (font_size / 2)
		);

		ImGui::Text(text.c_str(), args...);
		ImGui::NewLine();
	}

	void SceneTree::RenderConfirmation() {
		ImGui::SetNextWindowBgAlpha(0.8f);
		ImGui::SetNextWindowPos({ static_cast<float>(Settings::window_width) * (1.0f / 3.0f), static_cast<float>(Settings::window_height) * (1.0f / 3.0f) }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ static_cast<float>(Settings::window_width) * (1.0f / 3.0f), static_cast<float>(Settings::window_height) * (1.0f / 5.0f) }, ImGuiCond_Once);

		ImGui::Begin("SceneTree Confirmation", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		if (ImGui::BeginTable("Confirmation Table", 1)) {
			ImGui::TableNextColumn();
			char text_buffer_[64] = { '\0' };
			bool name_exists_{ false };
			std::stringstream ss;
			switch (confirmation_flag_) {
			case Confirmation::SAVE:
				TextCenter("[SAVING SCENE]");
				ss << new_entity_name_;
				/*if (new_entity_name_[0] == '\0') {
					TextCenter("Name not specified. Using default name:");
					TextCenter((*default_entity_name_).c_str());
				}
				else {
					TextCenter("You are about to save the current scene as:");
					TextCenter(ss.str().c_str());
				}*/
				if (reset_name_[0] == '\0')
				{
					TextCenter("You are about to save the current scene as:");
					TextCenter(current_scene_name_->c_str());
					ss.str("");
					ss << current_scene_name_->c_str();
				}
				else
				{
					TextCenter("You are about to save the current scene as:");
					TextCenter(reset_name_);
					ss.str("");
					ss << reset_name_;
				}

				ImGui::SameLine(ImGui::GetWindowSize().x / 2 - 100.0f);
				ImGui::PushItemWidth(200.0f);
				ImGui::InputText("##Rename", reset_name_, MAX_NAME_SIZE);
				ImGui::PopItemWidth();
				ImGui::SameLine();
				ImGui::Text(": Rename");
				/*ss.str("");
				ss << new_entity_name_;*/
				// check if input name already exists and warn the user
				for (auto& s : Serialize::scenes_) {
					if (s.first == ss.str()) {
						name_exists_ = true;
					}
				}
				if (name_exists_) {
					ImGui::NewLine();
					TextCenter("Scene already exists, do you want to overwrite existing?");
				}
				else {
					ImGui::NewLine();
					TextCenter("...");
				}
				ImGui::NewLine();
				ImGui::SameLine(ImGui::GetWindowSize().x / 4 - 50.0f);
				if (ImGui::Button("Confirm", ImVec2(100.0f, 0.0f))) {
					Serialize::SerializeScene(ecs_instance_, ss.str());
					Serialize::scenes_[ss.str()];
					/*if (reset_name_[0] == '\0') {
						Serialize::SerializeScene(ecs_instance_, *default_entity_name_);
						Serialize::scenes_[(*default_entity_name_)];
					}
					else {
						Serialize::SerializeScene(ecs_instance_, ss.str());
						Serialize::scenes_[ss.str()];
					}*/
					confirmation_flag_ = Confirmation::NONE;
				}
				ImGui::SameLine(ImGui::GetWindowSize().x / 4 * 3 - 50.0f);
				if (ImGui::Button("Cancel", ImVec2(100.0f, 0.0f))) {
					confirmation_flag_ = Confirmation::NONE;
				}
				break;
			case Confirmation::REMOVE:
				break;
			}
			ImGui::EndTable();
		}
		ImGui::End();
	}
}