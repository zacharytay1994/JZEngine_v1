/*	__FILE HEADER__
*	File:		SceneTree.cpp
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Renders all entities in the scene tree on the
				GUI using ImGui.
*/

#include "PCH.h"
#include "SceneTree.h"

#include "../EngineConfig.h"
#include "../ECS/ECSConfig.h"
#include "Console.h"
#include "../Resource/Serialize.h"
#include "MenuBar.h"
#include "../GraphicRendering/Renderers/RenderQueue.h"

#include "../SceneLogic/SceneLogic.h"

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
		ImGui::SetNextWindowSize ( { static_cast< float >( Settings::window_width ) * sx_, static_cast<float>(Settings::window_height - MenuBar::height_) * sy_ } , ImGuiCond_Always );
		ImGui::Begin ( "Scene Heirarchy" , 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::Button("Scene"))
			{
				view_ = VIEW::SCENE;
				scene_ = true;
			}
			if (ImGui::Button("Layers"))
			{
				view_ = VIEW::LAYER;
				scene_ = false;
				// rebuild layer data
				BuildLayerData();
			}
			if ( ImGui::Button ( "Logic" ) )
			{
				view_ = VIEW::LOGIC;
			}
			ImGui::EndMenuBar();
		}

		switch ( view_ )
		{
		case VIEW::SCENE:
			RenderScene ();
			break;
		case VIEW::LAYER:
			RenderLayers ();
			break;
		case VIEW::LOGIC:
			RenderLogic ();
			break;
		}

		/*if (scene_)
		{
			RenderScene();
		}
		else
		{
			RenderLayers();
		}*/
		

		ImGui::End();

		if (confirmation_flag_ != Confirmation::NONE) {
			RenderConfirmation();
		}
	}

	void SceneTree::RenderScene()
	{
		ImGui::Text("%s", current_scene_name_->c_str());
		ImGui::Separator();

		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("addicon")->GetRendererID()), { 15.0f, 15.0f }, { 0,1 }, { 1,0 } , -1 , { 0,0,0,0 } , EngineGUI::icon_col_ ))
		{
			// create a new entity, pushed into EntityManager
			unsigned int id = ecs_instance_->CreateEntity();

			// if successful
			if (id != -1)
			{
				// rename it
				ecs_instance_->GetEntity(id).name_ = GetName();
			}
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Add a new object to the scene.");
			ImGui::EndTooltip();
		}
		ImGui::SameLine();
		if (hide_)
		{
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("hideicon")->GetRendererID()), { 15.0f, 15.0f }, { 0,1 }, { 1,0 } , -1 , { 0,0,0,0 } , EngineGUI::icon_col_ ))
			{
				hide_ = !hide_;
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text("Show objects in scene hierarchy.");
				ImGui::EndTooltip();
			}
		}
		else
		{
			if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("showicon")->GetRendererID()), { 15.0f, 15.0f }, { 0,1 }, { 1,0 } , -1 , { 0,0,0,0 } , EngineGUI::icon_col_ ))
			{
				hide_ = !hide_;
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::Text("Hide objects in scene hierarchy.");
				ImGui::EndTooltip();
			}
		}
		ImGui::SameLine();
		if ( ImGui::ImageButton ( ( void* )static_cast< unsigned long long >( ResourceManager::GetTexture ( "saveicon" )->GetRendererID () ) , { 15.0f, 15.0f } , { 0,1 } , { 1,0 } , -1 , { 0,0,0,0 }, EngineGUI::icon_col_ ) )
		{
			confirmation_flag_ = Confirmation::SAVE;
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Save the scene.");
			ImGui::EndTooltip();
		}

		float window_width = ImGui::GetWindowWidth();
		ImGui::SameLine(window_width - 45.0f);
		if (ImGui::ImageButton((void*)static_cast<unsigned long long>(ResourceManager::GetTexture("deleteicon")->GetRendererID()), { 15.0f, 15.0f }, { 0,1 }, { 1,0 } , -1 , { 0,0,0,0 } , EngineGUI::icon_col_ ))
		{
			MenuBar::play_ = false;
			RemoveAllEntities();
		}
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Text("Remove all objects from scene.");
			ImGui::EndTooltip();
		}

		ImGui::Separator();
		// render text box for input name
		ImGui::InputText(" Name", new_entity_name_, MAX_NAME_SIZE);

		static ImGuiTextFilter filter;
		// Helper class to easy setup a text filter.
		// You may want to implement a more feature-full filtering scheme in your own application.
		filter.Draw(" Filter");

		ImGui::Separator();

		if (!hide_)
		{
			int popup_id{ 0 };
			// render all root entities in EntityManager
			for (auto& id : ecs_instance_->entity_manager_.root_ids_)
			{
				if (id != -1)
				{
					ECS::Entity* e = &ecs_instance_->entity_manager_.GetEntity(id);
					if (filter.PassFilter(e->name_.c_str()) && e->persistant_)
					{
						RenderAllChildObjects(e, ++popup_id);
					}
					// recursively render all children of a root entity
					//RenderAllChildObjects(&ecs_instance_->entity_manager_.GetEntity(id), ++popup_id);
				}
			}
		}
	}

	void SceneTree::RecursivelyAddChildObjectsToLayerData(ECS::Entity* entity)
	{
		// add to layers if has layer and texture component
		if (entity->HasComponent(1) && entity->HasComponent(2) && entity->persistant_)
		{
			layers_.emplace_back(entity->name_, entity->ecs_id_, &entity->GetComponent<SpriteLayer>().layer_, &entity->GetComponent<Texture>().texture_id_);
		}
		for (auto& c : entity->children_)
		{
			if (c != -1)
			{
				RecursivelyAddChildObjectsToLayerData(&ecs_instance_->entity_manager_.GetEntity(c));
			}
		}
	}

	void SceneTree::BuildLayerData()
	{
		layers_.clear();
		for (auto& id : ecs_instance_->entity_manager_.root_ids_)
		{
			if (id != -1)
			{
				ECS::Entity* e = &ecs_instance_->entity_manager_.GetEntity(id); 
				RecursivelyAddChildObjectsToLayerData(e);
			}
		}
	}

	bool CompareLayerPointer(SceneTree::LayerData a, SceneTree::LayerData b) { return (*a.layer_ < *b.layer_); }

	void SceneTree::RenderLayers()
	{
		//ImGui::SetNextWindowBgAlpha(1.0f);
		//ImGui::Begin("Scene Layer");
		//float width = ImGui::GetWindowWidth();
		ImGui::Separator();
		ImGui::Text("Back");
		ImGui::Separator();
		std::stringstream ss;
		//std::sort(RenderQueue::layers_.begin(), RenderQueue::layers_.end(), CompareLayerPointer);
		std::sort(layers_.begin(), layers_.end(), CompareLayerPointer);
		int i = std::numeric_limits<int>::min();
		//int uid = 0;
		//bool table_begin = false;
		for (auto& layer : layers_)
		{
			if (*layer.layer_ > i)
			{
				/*if (table_begin)
				{
					ImGui::EndTable();
					table_begin = false;
				}*/
				i = *layer.layer_;
				ss.str("");
				ss << "Layer " << *layer.layer_;
				ImGui::Text(ss.str().c_str());
				ImGui::Separator();
				//table_begin = ImGui::BeginTable(ss.str().c_str(), 2);
			}
			//ImGui::TableNextColumn();
			//ImGui::TableNextColumn();
			ss.str("");
			ss << "##" << layer.uid_;
			if (ImGui::BeginTable(ss.str().c_str(), 2))
			{
				ImGui::TableNextColumn();
				ImGui::Image((void*)static_cast<unsigned long long>(ResourceManager::GetTexture(*layer.texture_id_)->GetRendererID()), { 50.0f, 50.0f }, { 0,1 }, { 1,0 });
				ImGui::TableNextColumn();
				ImGui::Text(layer.name_.c_str());
				ImGui::InputInt(ss.str().c_str(), &*layer.layer_, 0);
				ImGui::EndTable();
			}
		}
		ImGui::Separator();
		ImGui::Text("Front");
		ImGui::Separator();
		//ImGui::End();
	}

	void SceneTree::RenderLogic ()
	{
		// display selection for all the functions
		if ( ImGui::BeginPopup ( "Inits" ) )
		{
			for ( auto& init : *SceneLogic::Instance().init_functions_ )
			{
				if ( ImGui::Selectable ( init.first.c_str () ) )
				{
					( *SceneLogic::Instance ().scene_inits_ )[ *current_scene_name_ ] = init.second;
					( *SceneLogic::Instance ().scene_inits_names_ )[ *current_scene_name_ ] = init.first;
				}
			};
			ImGui::EndPopup ();
		};

		if ( ImGui::BeginPopup ( "Updates" ) )
		{
			for ( auto& update : *SceneLogic::Instance ().update_functions_ )
			{
				if ( ImGui::Selectable ( update.first.c_str () ) )
				{
					( *SceneLogic::Instance ().scene_updates_ )[ *current_scene_name_ ] = update.second;
					( *SceneLogic::Instance ().scene_updates_names_ )[ *current_scene_name_ ] = update.first;
				}
			};
			ImGui::EndPopup ();
		};

		ImGui::Text ( "Scene Logic" );
		ImGui::Separator ();

		ImGui::Text ( "Init:" );
		if ( ( *SceneLogic::Instance ().scene_inits_ ).find ( *current_scene_name_ ) != ( *SceneLogic::Instance ().scene_inits_ ).end () )
		{
			if ( ImGui::Button ( ( *SceneLogic::Instance ().scene_inits_names_ )[ *current_scene_name_ ].c_str () , { ImGui::GetWindowWidth () * 0.9f, 0 } ) )
			{
				ImGui::OpenPopup ( "Inits" );
			}
		}
		else
		{
			if ( ImGui::Button ( "- Select -" , { ImGui::GetWindowWidth () * 0.9f, 0 } ) )
			{
				ImGui::OpenPopup ( "Inits" );
			}
		}

		ImGui::Text ( "Update:" );
		if ( ( *SceneLogic::Instance ().scene_updates_ ).find ( *current_scene_name_ ) != ( *SceneLogic::Instance ().scene_updates_ ).end () )
		{
			if ( ImGui::Button ( ( *SceneLogic::Instance ().scene_updates_names_ )[ *current_scene_name_ ].c_str() , { ImGui::GetWindowWidth () * 0.9f, 0 } ) )
			{
				ImGui::OpenPopup ( "Updates" );
			}
		}
		else
		{
			if ( ImGui::Button ( "- Select -" , { ImGui::GetWindowWidth () * 0.9f, 0 } ) )
			{
				ImGui::OpenPopup ( "Updates" );
			}
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
		ImGuiTreeNodeFlags tree_node_flag = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if(	selected_entity_id_ != -1	)
		{
			if( entity->entity_id_ == static_cast<ECS::ui32>(selected_entity_id_) )
			{
				is_selected = true;
				//ImGui::PushStyleColor ( ImGuiCol_TextSelectedBg , { 0.5f,0.5f,0.5f,1.0f } );
				tree_node_flag |= ImGuiTreeNodeFlags_Selected;
			}
		}

		bool open = ImGui::TreeNodeEx ( ss.str ().c_str () ,  tree_node_flag );

		// if a treenode is clicked, make that entity the selected_entity_
		if( ImGui::IsItemClicked () )
		{
			//selected_entity_ = entity;
			selected_entity_id_ = entity->entity_id_;
		}
		std::stringstream unique_popup_id_;
		unique_popup_id_ << id;
		if (ImGui::BeginPopupContextItem(unique_popup_id_.str().c_str()))
		{
			// adds an entity as a child of this entity on right click
			if( ImGui::Selectable ( "Add Entity" ) )
			{
				int temp_id = ecs_instance_->CreateEntity ( entity->entity_id_ );
				if(temp_id == -1 )
				{
					std::stringstream ss_warning;
					ss_warning << "Entity " << entity->name_ << " (ID: " << entity->entity_id_ << ") has maximum number of children!";
					//Console::Log(ss.str().c_str());
				}
				else
				{
					ECS::Entity& created_entity = ecs_instance_->GetEntity (temp_id);
					created_entity.name_ = GetName ();
				}
			}
			// removes an entity from the tree
			if( ImGui::Selectable ( "Remove Entity" ) )
			{
				ecs_instance_->RemoveEntity ( entity->entity_id_ );
				//selected_entity_ = nullptr;
				selected_entity_id_ = -1;
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
			//ImGui::PopStyleColor ();
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
		for (int i = static_cast<int>(ecs_instance_->entity_manager_.root_ids_.size() - 1); i >= 0; --i)
		{
			if (ecs_instance_->entity_manager_.root_ids_[i] != -1 && ecs_instance_->GetEntity(ecs_instance_->entity_manager_.root_ids_[i]).persistant_)
			{
				ecs_instance_->RemoveEntity(ecs_instance_->entity_manager_.root_ids_[i]);
			}
		}
		for (auto& name : *names_)
		{
			name.second = 0;
		}
		*current_scene_name_ = "New Scene";
		SceneLogic::Instance ().SetCurrentSceneName ( "New Scene" );
		selected_entity_id_ = -1;
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
			//char text_buffer_[64] = { '\0' };
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
					//Serialize::SerializeScene(ecs_instance_, ss.str());
					//Serialize::scenes_[ss.str()];
					///*if (reset_name_[0] == '\0') {
					//	Serialize::SerializeScene(ecs_instance_, *default_entity_name_);
					//	Serialize::scenes_[(*default_entity_name_)];
					//}
					//else {
					//	Serialize::SerializeScene(ecs_instance_, ss.str());
					//	Serialize::scenes_[ss.str()];
					//}*/
					//confirmation_flag_ = Confirmation::NONE;

					Serialize::SerializeScene2 ( ecs_instance_ , ss.str () );
					Serialize::scenes_[ ss.str () ];
					confirmation_flag_ = Confirmation::NONE;
				}
				ImGui::SameLine ();
				/*if ( ImGui::ImageButton ( ( void* )static_cast< unsigned long long >( ResourceManager::GetTexture ( "tempicon" )->GetRendererID () ) , { 10.0f, 10.0f } ) )
				{
					Serialize::SerializeScene2 ( ecs_instance_ , ss.str () );
					Serialize::scenes_[ ss.str () ];
					confirmation_flag_ = Confirmation::NONE;
				}*/
				ImGui::SameLine(ImGui::GetWindowSize().x / 4 * 3 - 50.0f);
				if (ImGui::Button("Cancel", ImVec2(100.0f, 0.0f))) {
					confirmation_flag_ = Confirmation::NONE;
				}
				/*if ( ImGui::Button ( "Confirm2" ) )
				{
					Serialize::SerializeScene2 ( ecs_instance_ , ss.str () );
					Serialize::scenes_[ ss.str () ];
					confirmation_flag_ = Confirmation::NONE;
				}*/
				break;
			case Confirmation::REMOVE:
				break;
			}
			ImGui::EndTable();
		}
		ImGui::End();
	}

	void SceneTree::SetSelectedEntity(int id)
	{
		selected_entity_id_ = id;
	}

	ECS::Entity* SceneTree::GetSelectedEntity()
	{
		if (selected_entity_id_ != -1)
		{
			return &ecs_instance_->GetEntity(selected_entity_id_);
		}
		return nullptr;
	}
}