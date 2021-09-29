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

		static bool SerializeEntity(ECS::Entity& entity);

		//static bool DeserializeEntity(ECS::Entity& entity, const std::string& name);

		static bool LoadEntity(ECS::Entity& entity, const std::string& name);

		static bool DeserializeEntityFromFile(const std::string& name);

		static void DeSerializeAllChildEntities(ECS::ECSInstance* ecs, std::ifstream& file);
		static void SerializeAllChildEntities(ECS::ECSInstance* ecs, std::ofstream& file, ECS::Entity& entity, int i);
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

		/*!_______________________________________________________________________________________________________*/
		/* STOP HERE GO NO FURTHER! */
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