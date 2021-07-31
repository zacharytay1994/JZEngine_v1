#pragma once

#include <memory>
#include <string>
#include <vector>
#include <array>
#include <bitset>
#include <stack>
#include <assert.h>
#include <iostream>
#include <unordered_map>

namespace JZEngine
{
	/*!
	 * @brief ___JZEngine::ECS___
	 * ****************************************************************************************************
	 * 1. This ECS only tailors to components with member data that do not allocate memory.
	 *	  If components contain e.g. std::vector, std::string etc, there will be memory leaks.
	 *	  Additional steps will have to be taken to handle such special components.
	 * 
	 *	  As such, make sure to only use non dynamic containers like std::array, or custom
	 *	  container types when creating components. This also ensures best data locality and
	 *	  minimized cache misses.
	 *	  ________________________________________
	 * 
	 * 2. All data storage of the ECS is allocated at compile time. Meaning variables like,
	 *	  MAX_COMPONENTS, MAX_ARCHETYPES, etc dictate how much memory is available for entities.
	 *	  
	 *    In the event that during runtime, the number archetypes for example, exceed the specified
	 *	  max, a message will be thrown on the console and there will be undefined behaviour. As
	 *	  the possible combinations of components will lead to a large number of possible
	 *	  archetypes, the MAX_ARCHETYPES number should be modified as seen fit.
	 *
	 *	  MAX_COMPONENTS should be known during compile time on the engine side, and should be
	 *	  modified as well to optimize memory usage. However, MAX_COMPONENTS will not be known
	 *    on the client side, as such, the client should be limited to creating a fixed number
	 *	  of components.
	 *	  ________________________________________
	 * 
	 * 3. Under the struct Archetype, the component_stride_ variable uses uint16_t(ui16) as its
	 *	  storage value. This means that the max size of each combination of components is limited
	 *    to 65'535 bytes. This is a pre-emptive space optimization. If need be, increase the 
	 *	  limit by changing the stored type to uint32_t(ui32), this will increase it to
	 *	  4'294'967'295 bytes.
	*/
	namespace ECS
	{
		typedef uint16_t ui16;
		typedef uint32_t ui32;
		typedef unsigned char ubyte;
		typedef unsigned long ulong;

		/* ECS MACROS */
		constexpr ui32 MAX_COMPONENTS			{ 256 };			/*!< arbitrary number */
		constexpr ui32 MAX_ARCHETYPES			{ 128 };			/*!< arbitrary number */
		constexpr ui32 CHUNKS_PER_ARCHETYPE		{ 256 };
		constexpr ui32 ENTITIES_PER_CHUNK		{ 256 };			/*!< arbitrary number */

		/* ____________________________________________________________________________________________________
		*																	COMPONENT DESCRIPTION DECLARATION
		   ____________________________________________________________________________________________________*/

		/*!
		 * @brief ___JZEngine::ECS::ComponentDescription___
		 * ****************************************************************************************************
		 * What defines an ecs component. Byte size, unique bit id,
		 * and a unique name. All registered components will have
		 * features defined by these data members.
		 * ****************************************************************************************************
		*/
		struct ComponentDescription
		{
			ComponentDescription(ui32 size, ui32 bit, std::string name);

			ui32		size_;	/*!< size in bytes of the component */
			ui32		bit_;	/*!< unique bit number assigned to this component, i.e. id */
			std::string	name_;	/*!< string name of the component */
		};

		/* ____________________________________________________________________________________________________
		*																		COMPONENT MANAGER DECLARATION
		   ____________________________________________________________________________________________________*/
		/*!
		 * @brief ___JZEngine::ECS::ComponentManager___
		 * ****************************************************************************************************
		 * Holds all component descriptions and provides these
		 * details to other parts of the ECS system when called 
		 * upon.
		 * ****************************************************************************************************
		*/
		struct ComponentManager
		{
			template <typename COMPONENT>
			static ComponentDescription		component_descriptions_;	/*!< template variable holding all the different component descriptions registered */
			std::unordered_map<std::string, bool> component_registered_;

			ComponentManager();
			~ComponentManager();

			/*!
			 * @brief ___JZEngine::ECS::ComponentManager::RegisterComponent()___
			 * ****************************************************************************************************
			 * Registers a struct or class as a component. Components should only 
			 * compose of member data and not member functions as they do not hold
			 * logic.
			 * ****************************************************************************************************
			 * @tparam COMPONENT 
			 * : The struct/class type to register.
			 * ****************************************************************************************************
			*/
			template <typename COMPONENT>
			void RegisterComponent()
			{
				if (component_registered_.find(typeid(COMPONENT).name()) == component_registered_.end())
				{
					component_descriptions_<COMPONENT> = ComponentDescription(sizeof(COMPONENT), bit_generator_++, typeid(COMPONENT).name());
					component_registered_[typeid(COMPONENT).name()] = 1;
					std::cout << "Registered Component: " << typeid(COMPONENT).name() << ", Bit: " << component_descriptions_<COMPONENT>.bit_ << std::endl;
				}
				else
				{
					std::cout << "WARNING! ComponentManager tried to re-register an existing component: " << typeid(COMPONENT).name() 
						<< ", Bit: " << component_descriptions_<COMPONENT>.bit_ << std::endl;
				}
			}

			///*!
			// * @brief ___JZEngine::ECS::ComponentManager::GetComponentDescription()___
			// * ****************************************************************************************************
			// * Gets a constant reference of a component description registers in the component database.
			// * ****************************************************************************************************
			// * @tparam COMPONENT 
			// * : The struct/class type to get the description of.
			// * @return ComponentDescription
			// * : A constant reference to the ComponentDescription.
			// * ****************************************************************************************************
			//*/
			//template <typename COMPONENT>
			//const ComponentDescription& GetComponentDescription() const
			//{
			//	return component_descriptions_<COMPONENT>;
			//}
		private:
			ui32							bit_generator_{0};			/*!< unique bit id to be assigned to newly registered components */
		};

		struct TestData
		{
			int x{10};
			int y{20};
		};

		struct TestData2
		{
			float z{3.0f};
			char c{'v'};
		};

		/* Forward declare Chunk for Archetype to get a handle to. */
		struct Archetype;

		/*!
		 * @brief ___JZEngine::ECS::Chunk___
		 * ****************************************************************************************************
		 * A chunk stores the data of entities in contiguous memory. 
		 * It handles the addition and deletion of entities, and the freeing
		 * and deleting of its memory.
		 * 
		 * CAUTION however if components of entities hold data that allocates
		 * memory such as std::vector and std::string, the chunk does not make
		 * sure to call the destructors of these objects. This will result
		 * in memory leaks.
		 * 
		 * As this ECS relies on contiguous memory to enhance performance, having
		 * data members that potentially introduces cache misses would defeat
		 * the purpose and hence is not considered.
		 * ****************************************************************************************************
		*/
		struct Chunk
		{
			Archetype*								owning_archetype_{nullptr};
			char*									data_{nullptr};
			ubyte									number_of_entities_{ 0 };
			ubyte									free_ids_count_{ 0 };
			std::array<ubyte, ENTITIES_PER_CHUNK>	free_ids_{ 0 };
			std::bitset<ENTITIES_PER_CHUNK>			active_flags_{ 0 };

			Chunk();
			~Chunk();

			void Initialize(Archetype* owner);

			/*!
			 * @brief ____JZEngine::ECS::Chunk::GetComponent()___
			 * ****************************************************************************************************
			 * Gets a component of a specific entity id. Navigates to where it is
			 * stored in data_ and casts it to the type then returning a reference.
			 * ****************************************************************************************************
			 * @tparam COMPONENT 
			 * : Component type to get.
			 * @param id
			 * : id of the entity to get the component from.
			 * @return COMPONENT&
			 * : Reference to the component of the entity.
			 * ****************************************************************************************************
			*/
			template <typename COMPONENT>
			COMPONENT& GetComponent(ui32 id);

			/*!
			 * @brief ___JZEngine::ECS::Chunk::AddEntity()___
			 * ****************************************************************************************************
			 * Adds a new entity to the chunk. Assumes that the chunk
			 * has enough space, either new, or previouly freed up.
			 * ****************************************************************************************************
			 * @return uint
			 * : Unique id of an entity only pertaining to this chunk.
			 * 
			 * @note
			 * : entity ids returned by this function are not unique throughout.
			 * It is only unique when coupled with the chunk, i.e. chunk & id together.
			 * ****************************************************************************************************
			*/
			ubyte AddEntity();

			/*!
			 * @brief ___JZEngine::ECS::Chunk::RemoveEntity()___
			 * ****************************************************************************************************
			 * Removes an entity from a chunk, setting its flag id to
			 * inactive (i.e. 0) and pushing it into the free_ids_ stack.
			 * ****************************************************************************************************
			 * @param id 
			 * : The id of the entity to remove.
			 * ****************************************************************************************************
			*/
			void RemoveEntity(ubyte id);

			/*!
			 * @brief ___ZeroEntityData___
			 * ****************************************************************************************************
			 * Zeros a portion of data_ occupied by an entity. 
			 * 
			 * CAUTION should be taken as the destructor of components
			 * that make up that entity is not called. This may lead to
			 * memory leaks if any kind of allocation happens with the
			 * creation of the component. E.g. using std::vector or
			 * std::string etc. These std objects will be zeroed out, 
			 * leaving the memory they are in charge of to be left in memory.
			 * 
			 * Note: Since the idea of an ECS is contiguous data, having
			 * dynamic memory allocation happen in a component defeats
			 * the purpose and hence is not accounted for.
			 * ****************************************************************************************************
			 * @param id
			 * : The id of the entity whos data to zero.
			 * ****************************************************************************************************
			*/
			void ZeroEntityData(ubyte id);

			/*!
			 * @brief ___ZeroAllData___
			 * ****************************************************************************************************
			 * Zeros out the entire memory held by the chunk.
			 * 
			 * CAUTION should be taken as the destructor of components
			 * that make up that entity is not called. This may lead to
			 * memory leaks if any kind of allocation happens with the
			 * creation of the component. E.g. using std::vector or
			 * std::string etc. These std objects will be zeroed out,
			 * leaving the memory they are in charge of to be left in memory.
			 *
			 * Note: Since the idea of an ECS is contiguous data, having
			 * dynamic memory allocation happen in a component defeats
			 * the purpose and hence is not accounted for.
			 * ****************************************************************************************************
			*/
			void ZeroAllData();

			/*!
			 * @brief ___IsFull___
			 * ****************************************************************************************************
			 * @return bool
			 * : If the chunk is full.
			 * ****************************************************************************************************
			*/
			bool IsFull();

			char* GetDataBegin(ubyte id);
		};

		/*!
		 * @brief ___JZEngine::ECS::Archetype___
		 * ****************************************************************************************************
		 * An ECS archetype is a unique combination of components. No two
		 * archetypes are the same. The archetype stores pointers to chunks
		 * of its component combination. The archetype also holds information
		 * such as chunk stride which represents the stride of one element in
		 * a chunk, and component stride which represents the stride of
		 * each component within one element.
		 * ****************************************************************************************************
		*/
		struct Archetype
		{
			ui32										id_{ MAX_ARCHETYPES };
			ui32										entity_stride_{ 0 };
			ui32										number_of_chunks_{ 0 };
			std::bitset<MAX_COMPONENTS>					mask_;
			std::array<Chunk, CHUNKS_PER_ARCHETYPE>		chunk_database_;
			std::array<ui16, MAX_COMPONENTS>			component_stride_{ 0 };	/*!< cumulative stride of each component,
																				assumes that cumulative stride will not
																				exceed 65'535 bytes. I.e. no combination
																				of components will exceed 65'535 bytes.*/

			Archetype();
			//Archetype(const Archetype& archetype);
			~Archetype();

			Archetype& operator=(const Archetype& archetype);

			void Initialize(ui32 id);

			/*!
			 * @brief ___JZEngine::ECS::Archetype::RegisterComponent()___
			 * ****************************************************************************************************
			 * Assigns the component stride to the component and appends
			 * the size to the total chunk stride. This will allow iteration
			 * over the components stored as bytes in dynamically allocated
			 * memory.
			 * ****************************************************************************************************
			 * @tparam COMPONENT
			 * : The component struct/class type to register
			 * ****************************************************************************************************
			*/
			template <typename COMPONENT>
			void RegisterComponent()
			{
				mask_[ComponentManager::component_descriptions_<COMPONENT>.bit_] = 1;
				component_stride_[ComponentManager::component_descriptions_<COMPONENT>.bit_] = entity_stride_;
				entity_stride_ += sizeof(COMPONENT);
			}

			/*!
			 * @brief ___JZEngine::ECS::Archetype::AddEntity()___
			 * ****************************************************************************************************
			 * Adds an entity into one of the chunks stored in this archetype. If
			 * no chunks with available space, create a new chunk.
			 * ****************************************************************************************************
			*/
			Chunk& AddEntity(ubyte& id);
		};

		struct ArchetypeManager
		{
			std::unordered_map<std::bitset<MAX_COMPONENTS>, ui32>			archetype_exist_tracker_;

			ArchetypeManager();
			~ArchetypeManager();

			template <typename...COMPONENTS>
			Archetype& GetArchetype()
			{
				// create mask
				std::bitset<MAX_COMPONENTS> mask;
				((mask[ComponentManager::component_descriptions_<COMPONENTS>.bit_] = 1), ...);

				// check if the mask already exist, if it does return the archetype
				if (archetype_exist_tracker_.find(mask) != archetype_exist_tracker_.end())
				{
					return archetype_database_[archetype_exist_tracker_[mask]];
				}

				if (number_of_archetypes_ >= MAX_ARCHETYPES)
				{
					std::cout << "ERROR! Too many archetypes generated! Increase MAX_ARCHETYPES value in ECS.h!" << std::endl;
					return archetype_database_[0];
				}

				// create it if does not exist
				archetype_database_[number_of_archetypes_].Initialize(number_of_archetypes_);
				archetype_exist_tracker_[mask] = number_of_archetypes_;

				// register all components into it
				((archetype_database_[number_of_archetypes_].RegisterComponent<COMPONENTS>()), ...);

				return archetype_database_[number_of_archetypes_++];
			}

			template <typename...COMPONENTS>
			Archetype& GetArchetype(const std::bitset<MAX_COMPONENTS>& currentmask)
			{
				// if currentmask is empty, create new archetype from new components
				if (currentmask.none())
				{
					return GetArchetype<COMPONENTS...>();
				}
				// else copy archetype and add components
				archetype_database_[number_of_archetypes_] = archetype_database_[archetype_exist_tracker_[currentmask]];
				Archetype& new_archetype = archetype_database_[number_of_archetypes_];
				((new_archetype.RegisterComponent<COMPONENTS>()), ...);
				new_archetype.id_ = number_of_archetypes_;
				archetype_exist_tracker_[new_archetype.mask_] = number_of_archetypes_;
				++number_of_archetypes_;
				return new_archetype;
			}

			ui32															number_of_archetypes_{ 0 };
			std::array<Archetype, MAX_ARCHETYPES>							archetype_database_;
		};

		struct System;
		struct SystemManager
		{
			std::vector<std::unique_ptr<System>> system_database_;
			std::unordered_map<std::string, bool> system_registered_;

			template <typename SYSTEM>
			void RegisterSystem()
			{
				if (system_registered_.find(typeid(SYSTEM).name()) == system_registered_.end())
				{
					system_database_.emplace_back(std::make_unique<SYSTEM>());
					system_registered_[typeid(SYSTEM).name()] = 1;
				}
				else
				{
					std::cout << "WARNING! SystemManager tried to re-register system: " << typeid(SYSTEM).name() << std::endl;
				}
			}

			void Update();
		};

		struct Entity;
		struct ECSInstance // destructor still missing
		{
			static ECSInstance& Instance();
			ComponentManager component_manager_;
			ArchetypeManager archetype_manager_;
			SystemManager system_manager_;
			int i = 0;

			void Update();

			template <typename SYSTEM>
			void RegisterSystem()
			{
				system_manager_.RegisterSystem<SYSTEM>();
			}

			/*template <typename...SYSTEMS>
			int CreateEntity();*/
		private:
			ECSInstance();
			std::vector<Entity> entities_;
		};

		template<typename COMPONENT>
		COMPONENT& Chunk::GetComponent(ui32 id)
		{
			assert(("Getting component that does not exist in Entity.",
				owning_archetype_->mask_[ECSInstance::Instance().component_manager_.component_descriptions_<COMPONENT>.bit_] == 1));

			// navigates to location of data
			char* data = data_ + (size_t)id * (size_t)owning_archetype_->entity_stride_ +
				(size_t)owning_archetype_->component_stride_[ComponentManager::component_descriptions_<COMPONENT>.bit_];

			// cast to type and return reference
			return *(reinterpret_cast<COMPONENT*>(data));
		}

		struct Entity
		{
			Chunk*								owning_chunk_{ nullptr };
			ubyte								id_{ 255 };

			Entity();
			~Entity();

			/*!
			 * @brief ___JZEngine::ECS::Entity::Initialize()___
			 * ****************************************************************************************************
			 * Initializes the entity and gets the unique archetype
			 * corresponding to its component combination. An id and
			 * chunk from that archetype will be returned.
			 * ****************************************************************************************************
			 * @tparam ...COMPONENTS 
			 * : Component combination of the entity.
			 * @param archetypeDatabase 
			 * : The archetype database that stores all archetypes.
			 * ****************************************************************************************************
			*/
			template <typename...COMPONENTS>
			void Initialize(ArchetypeManager& archetypeManager)
			{
				// get the new archetype based on this entities component combination
				Archetype& archetype = archetypeManager.GetArchetype<COMPONENTS...>();
				// add this new entity to the archetype
				owning_chunk_ = &archetype.AddEntity(id_);
				// initialize each component
				((owning_chunk_->GetComponent<COMPONENTS>(id_) = COMPONENTS()), ...);
			}

			/*!
			 * @brief ___JZEngine:ECS::Entity::GetComponent()___
			 * ****************************************************************************************************
			 * Gets a component within the entity. An assertion will
			 * be thrown if the component does not exist in the entity.
			 * ****************************************************************************************************
			 * @tparam COMPONENT 
			 * : Component to get.
			 * @return COMPONENT&
			 * : Reference to the component.
			 * ****************************************************************************************************
			*/
			template <typename COMPONENT>
			COMPONENT& GetComponent()
			{
				return owning_chunk_->GetComponent<COMPONENT>(id_);
			}

			template <typename...COMPONENTS>
			Entity& AddComponent()
			{
				((ECSInstance::Instance().component_manager_.RegisterComponent<COMPONENTS>()), ...);
				// check if this entity had a chunk before
				if (owning_chunk_)
				{
					// get the archetype of the new combination
					Archetype& new_archetype = ECSInstance::Instance().archetype_manager_.GetArchetype<COMPONENTS...>(owning_chunk_->owning_archetype_->mask_);

					// perform copy of entity over to the new archetype
					ubyte temp_id{ 0 };
					Chunk& temp_chunk = new_archetype.AddEntity(temp_id);

					// shallow copy
					memcpy(temp_chunk.GetDataBegin(temp_id), owning_chunk_->GetDataBegin(id_), owning_chunk_->owning_archetype_->entity_stride_);

					// tell old chunk to remove entity
					owning_chunk_->RemoveEntity(id_);

					// update owning_chunk and id
					owning_chunk_ = &temp_chunk;
					id_ = temp_id;
				}
				else
				{
					// get the new archetype based on this entities component combination
					Archetype& new_archetype = ECSInstance::Instance().archetype_manager_.GetArchetype<COMPONENTS...>();

					// add this new entity to the archetype
					owning_chunk_ = &new_archetype.AddEntity(id_);
				}

				// initialize all new components
				((owning_chunk_->GetComponent<COMPONENTS>(id_) = COMPONENTS()), ...);
				return *this;
			}
		};

		struct System
		{
			ubyte current_id_{ 0 };
			Chunk* current_chunk_{ nullptr };
			std::bitset<MAX_COMPONENTS> mask_;
			System()
			{
			}

			template <typename...COMPONENTS>
			void RegisterComponents()
			{
				((ECSInstance::Instance().component_manager_.RegisterComponent<COMPONENTS>()), ...);
				((mask_[ComponentManager::component_descriptions_<COMPONENTS>.bit_] = 1), ...);
				int i = ComponentManager::component_descriptions_<TestData>.bit_;
			}

			template <typename COMPONENT>
			COMPONENT& GetComponent()
			{
				assert(current_chunk_);
				return current_chunk_->GetComponent<COMPONENT>(current_id_);
			}

			virtual ~System() = default;
			/*virtual void PerFrame();
			virtual void Update();*/
			virtual void FrameBegin() { std::cout << "test" << std::endl; };
			virtual void Update(const float& dt) = 0;
		};
	}
}