/*	__FILE HEADER__
*	File:		Serialize.h
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Serializes components.
*/

#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include "../ECS/ECSConfig.h"
#include "ResourceManager.h"

#include "../UnreferencedParam.h"

namespace JZEngine
{
	namespace ECS
	{
		struct Entity;
	}
}

namespace JZEngine
{
	struct Serialize
	{
		static std::unordered_map<std::string, std::string> entities_;
		static std::unordered_map<std::string, bool> scenes_;

		enum class MODE
		{
			READ = 0,
			WRITE = 1
		};

		template <typename STREAM, typename ARG>
		static void StreamToArg ( STREAM& stream , ARG& arg )
		{
			if ( stream.peek () != 'c' )
			{
				stream >> arg;
				std::cout << arg << std::endl;
			}
			else
			{
				arg = ARG ();
				std::cout <<  "c detected" << stream.peek () << std::endl;
			}
		}

		template <typename STREAM, typename...ARGS>
		static void SERIALIZE(STREAM& stream, MODE mode, ARGS&&... args)
		{
			if ( mode == MODE::READ )
			{
				( ( stream >> args ) , ... );
			}
			else
			{
				( ( stream << args << " " ) , ... );
			}
		}

		static void Load();
		static void Save();

		static bool SerializeEntity(ECS::ECSInstance* ecs, ECS::Entity& entity);
		static int	LoadEntity(ECS::ECSInstance* ecs, const std::string& name);
		static void	ReInitializeEntity(ECS::ECSInstance* ecs, const std::string& prefab, int entityID);
		static bool DeserializeEntityFromFile(const std::string& name);
		static void ListAllSceneFiles();
		static void ListAllPrefabFiles();

		template <typename STREAM>
		static int DeSerializeAllChildEntities ( ECS::ECSInstance* ecs , STREAM& file , std::stringstream& ss , unsigned int parent = -1 )
		{
			// read line of file
			// if no parent
			int id;
			if ( parent == -1 )
			{
				id = ecs->CreateEntity ();
			}
			else // else create with parent
			{
				id = ecs->CreateEntity ( parent );
			}
			ECS::Entity& entity = ecs->entity_manager_.GetEntity ( id );
			// read data and load entity
			ss >> entity.name_;
			int children;
			ss >> children;

			// deserialize all components
			char c;
			while ( ss >> c )
			{
				switch ( c )
				{
				case 'c':
					int i;
					ss >> i;
					entity.AddComponent ( i );
					DeSerializeECSConfigComponent ( ECS::ECSConfig::Component () , i , entity , ss );
					break;
				}
			}

			// deserialize all children
			for ( int i = 0; i < children; ++i )
			{
				std::string line;
				std::getline ( file , line );
				std::stringstream next_ss;
				next_ss << line;
				DeSerializeAllChildEntities ( ecs , file , next_ss , id );
			}

			return id;
		}

		template <typename STREAM>
		static int DeSerializeAllChildEntities2(ECS::ECSInstance* ecs, STREAM& file, std::stringstream& ss, unsigned int parent = -1)
		{
			// read line of file
			// if no parent
			int id;
			if (parent == -1)
			{
				id = ecs->CreateEntity();
			}
			else // else create with parent
			{
				id = ecs->CreateEntity(parent);
			}
			ECS::Entity& entity = ecs->entity_manager_.GetEntity(id);
			// read data and load entity
			ss >> entity.name_;
			int children;
			ss >> children;

			// deserialize all components
			char c;
			while (ss >> c)
			{
				switch (c)
				{
				case 'c':
					int i;
					ss >> i;
					entity.AddComponent(i);
					std::string component_name;
					ss >> component_name;
					ss >> component_name;
					DeSerializeECSConfigComponent(ECS::ECSConfig::Component(), i, entity, ss);
					break;
				}
			}

			// deserialize all children
			for (int i = 0; i < children; ++i)
			{
				std::string line;
				std::getline(file, line);
				std::stringstream next_ss;
				while ( line[ 0 ] != '!' )
				{
					next_ss << line;
					std::getline ( file , line );
				}
				DeSerializeAllChildEntities2(ecs, file, next_ss, id);
			}

			return id;
		}

		template <typename STREAM>
		static void ReInitializeAllChildEntities(ECS::ECSInstance* ecs, STREAM& file, std::stringstream& ss, int entityID/*, unsigned int parent = -1*/)
		{
			// read line of file
			// if no parent
			//int id;
			//if (parent == -1)
			//{
			//	id = entityID;
			//}
			//else // else create with parent
			//{
			//	id = ecs->CreateEntity(parent);
			//}
			ECS::Entity& entity = ecs->entity_manager_.GetEntity(entityID);
			// read data and load entity
			ss >> entity.name_;
			int children;
			ss >> children;

			// deserialize all components
			char c;
			while (ss >> c)
			{
				switch (c)
				{
				case 'c':
					int i;
					ss >> i;
					DeSerializeECSConfigComponent(ECS::ECSConfig::Component(), i, entity, ss);
					break;
				}
			}

			// deserialize all children
			/*for (auto& child : entity.children_)
			{
				if (child != -1)
				{
					ReInitializeAllChildEntities(ecs, file, next_ss, child);
				}
			}*/
			for (int i = 0; i < children; ++i)
			{
				std::string line;
				std::getline(file, line);
				std::stringstream next_ss;
				next_ss << line;
				ReInitializeAllChildEntities(ecs, file, next_ss, entity.children_[i]);
			}
		}

		static void DeserializeScene(ECS::ECSInstance* ecs, const std::string& name);
		static void DeserializeScene2( ECS::ECSInstance* ecs , const std::string& name );

		static void SerializeAllChildEntities (ECS::ECSInstance* ecs, std::ofstream& file, ECS::Entity& entity);
		static void SerializeAllChildEntities2 ( ECS::ECSInstance* ecs , std::ofstream& file , ECS::Entity& entity );
		static bool SerializeScene(ECS::ECSInstance* ecs_instance_, const std::string& name);
		static bool SerializeScene2 ( ECS::ECSInstance* ecs_instance_ , const std::string& name );

		template <typename COMPONENT>
		static void SerializeComponent(COMPONENT& component, std::stringstream& stream, MODE mode = MODE::WRITE)
		{
			UNREFERENCED_PARAMETER(component);
			UNREFERENCED_PARAMETER(stream);
			UNREFERENCED_PARAMETER(mode);
			Log::Warning("Serialize", "- Unsure how to serialize {}. Have you specialized your serialize in Serialize.h?",
				typeid(COMPONENT).name());
		}

		template <>
		static void SerializeComponent(Transform& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.position_.x,
				component.position_.y,
				component.child_position_.x,
				component.child_position_.y,
				component.rotation_,
				component.scale_.x,
				component.scale_.y,
				component.size_.x,
				component.size_.y);
		}

		template <>
		static void SerializeComponent(SpriteLayer& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.layer_);
		}
		
		template <>
		static void SerializeComponent(Texture& component, std::stringstream& stream, MODE mode)
		{
			if (mode == MODE::WRITE)
			{
				// get string representation of texture_id
				for (auto& rm : ResourceManager::umap_texture2ds_)
				{
					if (component.texture_id_ == rm.second)
					{
						std::string write_string = rm.first;
						SERIALIZE(stream, mode, write_string);
					}
				}
			}
			else if (mode == MODE::READ)
			{
				// set int representation of string
				std::string read_string;
				SERIALIZE(stream, mode, read_string);
				if (ResourceManager::umap_texture2ds_.find(read_string) != ResourceManager::umap_texture2ds_.end())
				{
					component.texture_id_ = ResourceManager::umap_texture2ds_[read_string];
				}
				else
				{
					component.texture_id_ = ResourceManager::umap_texture2ds_["imagenotfound"];
				}
			}
		}
		
		template <>
			static void SerializeComponent(NonInstanceShader& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.shader_id_,
				component.tint.x,
				component.tint.y,
				component.tint.z);
		}

		template <>
		static void SerializeComponent(PhysicsComponent& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.player,
				
				component.position.x,
				component.position.y,
				component.rotation,
				component.angularVelocity,
				component.Density,
				component.Restitution,
				component.IsStatic
				);
		}
		
		template <>
		static void SerializeComponent(CollisionComponent& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.offset.x,
				component.offset.y,
				component.shapeid,
				component.size.x,
				component.size.y
			);
		}

		template <>
		static void SerializeComponent(InstanceShader& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.shader_id_);
		}
		
		template <>
		static void SerializeComponent(Parallax& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.is_vertical,
				component.speed_x_,
				component.speed_y_);
		}

		template <>
		static void SerializeComponent(Animation2D& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.animation_check_,
				component.animation_counter_,
				component.animation_speed_,
				component.column_,
				component.frame_,
				component.max_frames_,
				component.rows_);
		}

		template <>
		static void SerializeComponent(RandomMovement& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.direction_.x,
				component.direction_.y);
		}

		template <>
		static void SerializeComponent(MouseEvent& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.bounding_half_width_,
				component.bounding_half_height_);
		}

		template <>
		static void SerializeComponent(TextData& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.font_size_);
		}

		template <>
		static void SerializeComponent ( CustomLogicContainer& component , std::stringstream& stream , MODE mode )
		{
			if ( mode == MODE::WRITE )
			{
				// get string representation of texture_id
				for ( int i = 0; i < MAX_LOGIC_PER_ENTITY; ++i )
				{
					SERIALIZE ( stream , mode , LogicContainer::Instance ().GetUpdateName ( component.updates[ i ] ) );
				}
			}
			else if ( mode == MODE::READ )
			{
				// get string representation of texture_id
				for ( int i = 0; i < MAX_LOGIC_PER_ENTITY; ++i )
				{
					std::string name;
					SERIALIZE ( stream , mode , name );
					component.updates[ i ] = LogicContainer::Instance ().GetUpdateID(name);
				}
			}
		}

		template <>
		static void SerializeComponent ( CustomDataContainer& component , std::stringstream& stream , MODE mode )
		{
			if ( mode == MODE::WRITE )
			{
				// serialize initialized flag
				SERIALIZE ( stream , mode , component.initialized );
				// serialize data
				for ( int i = 0; i < CustomDataContainer::CUSTOM_DATA_SIZE; ++i )
				{
					SERIALIZE ( stream , mode , component.data[ i ] );
				}
			}
			else if ( mode == MODE::READ )
			{
				// deserialize initialized flag
				SERIALIZE ( stream , mode , component.initialized );
				// deserialize data
				for ( int i = 0; i < CustomDataContainer::CUSTOM_DATA_SIZE; ++i )
				{
					SERIALIZE ( stream , mode , component.data[ i ] );
				}
			}
		}

		template <>
		static void SerializeComponent ( AnimatedTransformComponent& component , std::stringstream& stream , MODE mode )
		{
			SERIALIZE ( stream , mode ,
				component.speed_ ,
				component.modulate_rotation_ ,
				component.modulate_scale_.x ,
				component.modulate_scale_.y );
		}

		template <>
		static void SerializeComponent ( LeafParticleSystemComponent& component , std::stringstream& stream , MODE mode )
		{
			SERIALIZE ( stream , mode ,
				component.emission_rate_ ,
				component.wind_speed_ ,
				component.wind_direction_ ,
				component.wind_spread_ );
		}

		/*!_______________________________________________________________________________________________________*/
		/* STOP HERE GO NO FURTHER! */ // WHY NOT
		/*!_______________________________________________________________________________________________________*/
		template <size_t I = 0, typename...TUPLE>
		static typename std::enable_if<I == sizeof...(TUPLE), void>::type
			SerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity, std::stringstream& stream)
		{
			UNREFERENCED_PARAMETER(t);
			UNREFERENCED_PARAMETER(i);
			UNREFERENCED_PARAMETER(entity);
			UNREFERENCED_PARAMETER(stream);
			Log::Warning("Serialize", "- SerializeECSConfigComponent::tuple size exceeded.");
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		static typename std::enable_if < I < sizeof...(TUPLE), void>::type
			SerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity, std::stringstream& stream)
		{
			if (I == i)
			{
				using COMPONENT = decltype(std::get<I>(t));
				SerializeComponent<std::remove_reference_t<COMPONENT>>(entity.GetComponent<std::remove_reference_t<COMPONENT>>(), stream, MODE::WRITE);
				return;
			}
			SerializeECSConfigComponent<I + 1>(t, i, entity, stream);
		}

		template <size_t I = 0, typename...TUPLE>
		static typename std::enable_if<I == sizeof...(TUPLE), void>::type
			DeSerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity, std::stringstream& stream)
		{
			UNREFERENCED_PARAMETER(t);
			UNREFERENCED_PARAMETER(i);
			UNREFERENCED_PARAMETER(entity);
			UNREFERENCED_PARAMETER(stream);
			Log::Warning("Serialize", "- DeSerializeECSConfigComponent::tuple size exceeded.");
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		static typename std::enable_if < I < sizeof...(TUPLE), void>::type
			DeSerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity, std::stringstream& stream)
		{
			if (I == i)
			{
				using COMPONENT = decltype(std::get<I>(t));
				SerializeComponent<std::remove_reference_t<COMPONENT>>(entity.GetComponent<std::remove_reference_t<COMPONENT>>(), stream, MODE::READ);
				return;
			}
			DeSerializeECSConfigComponent<I + 1>(t, i, entity, stream);
		}
	};
}