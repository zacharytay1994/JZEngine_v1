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

		template <typename STREAM, typename...ARGS>
		static void SERIALIZE(STREAM& stream, MODE mode, ARGS&&... args)
		{
			if (mode == MODE::READ)
			{
				((stream >> args), ...);
			}
			else
			{
				((stream << args << " "), ...);
			}
		}

		static void Load();
		static void Save();

		static bool SerializeEntity(ECS::ECSInstance* ecs, ECS::Entity& entity);
		static bool LoadEntity(ECS::ECSInstance* ecs, const std::string& name);
		static bool DeserializeEntityFromFile(const std::string& name);
		static void ListAllSceneFiles();
		static void ListAllPrefabFiles();

		template <typename STREAM>
		static void DeSerializeAllChildEntities(ECS::ECSInstance* ecs, STREAM& file, std::stringstream& ss, unsigned int parent = -1)
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
				next_ss << line;
				DeSerializeAllChildEntities(ecs, file, next_ss, id);
			}
		}

		static void DeserializeScene(ECS::ECSInstance* ecs, const std::string& name);
		static void SerializeAllChildEntities(ECS::ECSInstance* ecs, std::ofstream& file, ECS::Entity& entity);
		static bool SerializeScene(ECS::ECSInstance* ecs_instance_, const std::string& name);

		template <typename COMPONENT>
		static void SerializeComponent(COMPONENT& component, std::stringstream& stream, MODE mode = MODE::WRITE)
		{
			Log::Warning("Serialize", "- Unsure how to serialize {}. Have you specialized your serialize in Serialize.h?",
				typeid(COMPONENT).name());
		}

		template <>
		static void SerializeComponent(Transform& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.position_.x,
				component.position_.y,
				component.rotation_,
				component.scale_.x,
				component.scale_.y,
				component.size_.x,
				component.size_.y);
		}
		
		template <>
		static void SerializeComponent(Texture& component, std::stringstream& stream, MODE mode)
		{
			SERIALIZE(stream, mode,
				component.texture_id_);
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
				component.shapeid,
				component.position.x,
				component.position.y,
				component.rotation,
				component.rotationalVelocity,
				component.Density,
				component.Restitution,
				component.IsStatic
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

		/*!_______________________________________________________________________________________________________*/
		/* STOP HERE GO NO FURTHER! */ // WHY NOT
		/*!_______________________________________________________________________________________________________*/
		template <size_t I = 0, typename...TUPLE>
		static typename std::enable_if<I == sizeof...(TUPLE), void>::type
			SerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity, std::stringstream& stream)
		{
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