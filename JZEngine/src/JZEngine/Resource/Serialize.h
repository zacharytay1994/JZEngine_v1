#pragma once
#include <string>
#include <fstream>
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
		#define SERIALIZE(file, val) (file << val << " ");
		#define DESERIALIZE(file, val) (file >> val);

		static bool SerializeEntity(ECS::Entity& entity);

		static bool DeserializeEntity(ECS::Entity& entity);

		template <typename COMPONENT>
		static void SerializeComponent(COMPONENT& component, std::ofstream& file)
		{
			Log::Warning("Serialize", "Unsure how to serialize {}. Have you specialized your serialize in Serialize.h?",
				typeid(COMPONENT).name());
		}

		template <typename COMPONENT>
		static void DeSerializeComponent(COMPONENT& component, std::ifstream& file)
		{
			Log::Warning("Serialize", "Unsure how to deserialize {}. Have you specialized your serialize in Serialize.h?",
				typeid(COMPONENT).name());
		}

		template <>
		static void SerializeComponent(Transform& component, std::ofstream& file)
		{
			SERIALIZE(file, component.position_.x);
			SERIALIZE(file, component.position_.y);
			SERIALIZE(file, component.rotation_);
			SERIALIZE(file, component.scale_.x);
			SERIALIZE(file, component.scale_.y);
			SERIALIZE(file, component.size_.x);
			SERIALIZE(file, component.size_.y);
		}

		template <>
		static void DeSerializeComponent(Transform& component, std::ifstream& file)
		{
			DESERIALIZE(file, component.position_.x);
			DESERIALIZE(file, component.position_.y);
			DESERIALIZE(file, component.rotation_);
			DESERIALIZE(file, component.scale_.x);
			DESERIALIZE(file, component.scale_.y);
			DESERIALIZE(file, component.size_.x);
			DESERIALIZE(file, component.size_.y);
		}

		/*!_______________________________________________________________________________________________________*/
		/* STOP HERE GO NO FURTHER! */
		/*!_______________________________________________________________________________________________________*/
		template <size_t I = 0, typename...TUPLE>
		static typename std::enable_if<I == sizeof...(TUPLE), void>::type
			SerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity, std::ofstream& file)
		{
			Log::Warning("Serialize", "SerializeECSConfigComponent::tuple size exceeded.");
			return;
		}

		template <size_t I = 0, typename...TUPLE>
		static typename std::enable_if < I < sizeof...(TUPLE), void>::type
			SerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i, ECS::Entity& entity, std::ofstream& file)
		{
			if (I == i)
			{
				using COMPONENT = decltype(std::get<I>(t));
				SerializeComponent<std::remove_reference_t<COMPONENT>>(entity.GetComponent<std::remove_reference_t<COMPONENT>>(), file);
				return;
			}
			SerializeECSConfigComponent<I + 1>(t, i, entity, file);
		}

	};

	/*template <size_t I = 0, typename...TUPLE>
	static typename std::enable_if<I == sizeof...(TUPLE), void>::type
		DeSerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i)
	{
		Log::Warning("Serialize", "DeSerializeECSConfigComponent::tuple size exceeded.");
		return;
	}

	template <size_t I = 0, typename...TUPLE>
	static typename std::enable_if < I < sizeof...(TUPLE), void>::type
		DeSerializeECSConfigComponent(std::tuple<TUPLE...> t, size_t i)
	{
		if (I == i)
		{
			using COMPONENT = decltype(std::get<I>(t));
			DeSerializeComponent < std::remove_reference_t<COMPONENT>();
			return;
		}
		DeSerializeECSConfigComponent<I + 1>(t, i);
	}*/
}