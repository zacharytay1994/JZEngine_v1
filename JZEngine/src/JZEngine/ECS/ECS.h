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

struct TestComponent
{
	int x{ -90 }, y{ -5 };
};

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
		constexpr ui32 CHUNKS_PER_ARCHETYPE		{ 256 };			/*!< arbitrary number */
		constexpr ui32 ENTITIES_PER_CHUNK		{ 256 };			/*!< arbitrary number */

		using SystemComponents = std::array<ui32, MAX_COMPONENTS>;

		using ComponentMask = std::bitset<MAX_COMPONENTS>;

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
			ComponentDescription() = default;
			ComponentDescription(ui32 size, ui32 bit, std::string name);

			ui32		size_	{ 0 };						/*!< size in bytes of the component */
			ui32		bit_	= static_cast<ui32>(-1);	/*!< unique bit number assigned to this component, i.e. id */
			std::string	name_;								/*!< string name of the component */
			bool		registered_{ 0 };
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
			static ComponentDescription				component_descriptions_;	/*!< template variable holding all the different component descriptions registered */
			std::array<ui32, MAX_COMPONENTS>		component_sizes_{ 0 };		/*!< a way to access component sizes through their id */

			struct ComponentNameID
			{
				std::string		name_;
				unsigned int	bit_;
			};
			std::vector<ComponentNameID> registered_components_;

			ComponentManager();
			~ComponentManager();

			template <typename COMPONENT>
			bool ComponentRegistered()
			{
				std::cout << typeid(COMPONENT).name() << "," << component_descriptions_<COMPONENT>.registered_ << std::endl;
				return component_descriptions_<COMPONENT>.registered_;
			}

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
				// check if component has been registered before
				if (ComponentRegistered<COMPONENT>())
				{
					std::cout << "WARNING! ComponentManager tried to re-register an existing component: " << typeid(COMPONENT).name()
						<< ", Bit: " << component_descriptions_<COMPONENT>.bit_ << std::endl;
				}
				else
				{
					component_sizes_[bit_generator_] = sizeof(COMPONENT);
					component_descriptions_<COMPONENT> = ComponentDescription(sizeof(COMPONENT), bit_generator_++, typeid(COMPONENT).name());
					std::cout << "Registered Component: " << typeid(COMPONENT).name() << ", Bit: " << component_descriptions_<COMPONENT>.bit_ << std::endl;
					component_descriptions_<COMPONENT>.registered_ = 1;
					registered_components_.push_back({ typeid(COMPONENT).name(), component_descriptions_<COMPONENT>.bit_ });
				}
			}

			template <size_t I = 0, typename...TUPLE>
			typename std::enable_if<I == sizeof...(TUPLE), void>::type
			RegisterTuple(std::tuple<TUPLE...> t)
			{
				// no more tuples to iterate over, return void
				return;
			}

			template <size_t I = 0, typename...TUPLE>
			typename std::enable_if<I < sizeof...(TUPLE), void>::type
			RegisterTuple(std::tuple<TUPLE...> t)
			{
				RegisterComponent<std::tuple_element_t<I, std::tuple<TUPLE...>>>();
				RegisterTuple<I + 1>(t);
			}

			void RegisterConfigComponents();

		private:
			ui32								bit_generator_{0};			/*!< unique bit id to be assigned to newly registered components */
		};

		/* Forward declare Archetype for Chunk to get a handle to. */
		struct Archetype;

		/* ____________________________________________________________________________________________________
		*																					CHUNK DECLARATION
		   ____________________________________________________________________________________________________*/

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
			ui32									id_ = -1;
			Archetype*								owning_archetype_{nullptr};		/*!< the archetype object storing this chunk */
			std::unique_ptr<char[]>					data_{nullptr};					/*!< component data stored in bytes */
			//char* data_{ nullptr };
			ubyte									number_of_entities_{ 0 };		/*!< number of entities stored in this chunk */
			ubyte									free_ids_count_{ 0 };			/*!< number of free ids, i.e. previouly deleted entity spots */
			std::array<ubyte, ENTITIES_PER_CHUNK>	free_ids_{ 0 };					/*!< the free id spots */
			std::bitset<ENTITIES_PER_CHUNK>			active_flags_{ 0 };				/*!< represents which entities by id are active */

			Chunk();
			~Chunk();

			/*!
			 * @brief ___JZEngine::ECS::Chunk::Initialize()___
			 * ****************************************************************************************************
			 * Sets the owning archetype of the chunk and allocates data_ bytes.
			 * ****************************************************************************************************
			 * @param owner
			 * : Pointer to the owning archetype object.
			 * ****************************************************************************************************
			*/
			void Initialize(Archetype* owner, ui32 id);

			/*!
			 * @brief ___JZEngine::ECS::Chunk::GetComponent()___
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

			/*!
			 * @brief ___JZEngine::ECS::Chunk::GetDataBegin()___
			 * ****************************************************************************************************
			 * Gets the start of memory of an entity.
			 * ****************************************************************************************************
			*/
			char* GetDataBegin(ubyte id);

			void Print();
		};

		/* ____________________________________________________________________________________________________
		*																				ARCHETYPE DECLARATION
		   ____________________________________________________________________________________________________*/

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
			ui32										id_{ MAX_ARCHETYPES };	/*!< unique id of the archetype */
			ui32										entity_stride_{ 0 };	/*!< size in bytes of each entity, i.e. combination of components */
			ui32										number_of_chunks_{ 0 };	/*!< current number of chunks in this archetype */
			std::bitset<MAX_COMPONENTS>					mask_;					/*!< unique component combination representing this archetype */
			std::array<Chunk, CHUNKS_PER_ARCHETYPE>		chunk_database_;		/*!< storage chunk objects */
			std::array<ui16, MAX_COMPONENTS>			component_stride_{ 0 };	/*!< cumulative stride of each component,
																				assumes that cumulative stride will not
																				exceed 65'535 bytes. I.e. no combination
																				of components will exceed 65'535 bytes.*/

			Archetype();
			~Archetype();

			/*!
			 * @brief ___JZEngine::ECS::Archetype::operator=()___
			 * ****************************************************************************************************
			 * Only copies entity_stride_, mask_, and component_stride_.
			 * Mainly used to create a new archetype that this archetype's
			 * description if a subset of.
			 * ****************************************************************************************************
			*/
			Archetype& operator=(const Archetype& archetype);

			/*!
			 * @brief ___JZEngine::ECS::Archetype::Initialize()___
			 * ****************************************************************************************************
			 * Sets the unique id of this archetype.
			 * ****************************************************************************************************
			 * @param id
			 * : Unique id to set.
			 * ****************************************************************************************************
			*/
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
			 * @brief ___JZEngine::ECS::Archetype::RegisterComponent()___
			 * ****************************************************************************************************
			 * Assigns the component stride to the component and appends
			 * the size to the total chunk stride. This will allow iteration
			 * over the components stored as bytes in dynamically allocated
			 * memory.
			 * ****************************************************************************************************
			 * @param bit
			 * : The unique component bit from the component manager to register.
			 * ****************************************************************************************************
			*/
			void RegisterComponent(ui32 bit);

			/*!
			 * @brief ___JZEngine::ECS::Archetype::AddEntity()___
			 * ****************************************************************************************************
			 * Adds an entity into one of the chunks stored in this archetype. If
			 * no chunks with available space, create a new chunk.
			 * ****************************************************************************************************
			*/
			Chunk& AddEntity(ubyte& id);

			// for debugging purposes
			void Print();
		};

		/* ____________________________________________________________________________________________________
		*																		ARCHETYPE MANAGER DECLARATION
		   ____________________________________________________________________________________________________*/

		/*!
		 * @brief ___JZEngine::ECS::ArchetypeManager___
		 * ****************************************************************************************************
		 * Holds all unique archetypes, i.e. unique combination of components.
		 * Makes sure there can only be one instance of each unique archetype exists.
		 * ****************************************************************************************************
		*/
		struct ArchetypeManager
		{
			std::unordered_map<std::bitset<MAX_COMPONENTS>, ui32>			archetype_exist_tracker_;	/*!< used to check if an archetype already exists,
																											 mainly to prevent iteration over fixed size array
																											 of archetype database. */

			ArchetypeManager();
			~ArchetypeManager();

			/*!
			 * @brief ___JZEngine::ECS::GetArchetype()___
			 * ****************************************************************************************************
			 * Returns an archetype of the component combination provided. If non exists,
			 * creates it and returns.
			 * ****************************************************************************************************
			 * @tparam ...COMPONENTS 
			 * : Component combination.
			 * @return Archetype&
			 * : The archetype of the component combination.
			 * ****************************************************************************************************
			*/
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

			/*!
			 * @brief ___JZEngine::ECS::GetArchetype()___
			 * ****************************************************************************************************
			 * Returns an archetype of the component combination provided as an array
			 * of bits. If non exists, creates it and returns.
			 * ****************************************************************************************************
			 * @param bits
			 * : Component combination.
			 * @return Archetype&
			 * : The archetype of the component combination.
			 * ****************************************************************************************************
			*/
			Archetype& GetArchetype(const std::array<ui32, MAX_COMPONENTS>& bits);

			/*!
			 * @brief ___JZEngine::ECS::GetArchetype()___
			 * ****************************************************************************************************
			 * Returns an archetype of the component combination combined with
			 * current component combination. Returns existing or creates a new archetype.
			 * ****************************************************************************************************
			 * @tparam ...COMPONENTS 
			 * : Additional component combination.
			 * @param currentmask 
			 * : Current component combination.
			 * @return 
			 * : The archetype of the combined component combination.
			 * ****************************************************************************************************
			*/
			template <typename...COMPONENTS>
			Archetype& GetArchetype(const std::bitset<MAX_COMPONENTS>& currentmask)
			{
				// if currentmask is empty, create new archetype from new components
				if (currentmask.none())
				{
					return GetArchetype<COMPONENTS...>();
				}
				// build new mask
				std::bitset<MAX_COMPONENTS> new_mask = currentmask;
				((new_mask[ComponentManager::component_descriptions_<COMPONENTS>.bit_] = 1), ...);
				// check if new archetype exists
				if (archetype_exist_tracker_.find(new_mask) != archetype_exist_tracker_.end())
				{
					// return this archetype
					return archetype_database_[archetype_exist_tracker_[new_mask]];
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

			/*!
			 * @brief ___JZEngine::ECS::GetArchetype()___
			 * ****************************************************************************************************
			 * Returns an archetype of the component combination combined with
			 * current component combination. Returns existing or creates a new archetype.
			 * ****************************************************************************************************
			 * @param currentmask
			 * : Current component combination.
			 * @param bits
			 * : Additional component combination.
			 * @return
			 * : The archetype of the combined component combination.
			 * ****************************************************************************************************
			*/
			Archetype& GetArchetype(const std::bitset<MAX_COMPONENTS>& currentmask, const std::array<ui32, MAX_COMPONENTS>& bits);

			// for debugging purposes
			void Print();

			ui32															number_of_archetypes_{ 0 };	/*!< number of unique archetypes created */
			std::array<Archetype, MAX_ARCHETYPES>							archetype_database_;		/*!< storage of all unique archetype objects */
		};

		/* Forward declare System for SystemManager to get a handle to. */
		struct System;

		/* ____________________________________________________________________________________________________
		*																			SYSTEM MANAGER DECLARATION
		   ____________________________________________________________________________________________________*/

		/*!
		 * @brief ___JZEngine::ECS::SystemManager___
		 * ****************************************************************************************************
		 * Holds all registered systems, and updates them per frame with matching
		 * archetypes with the same component combination signature.
		 * ****************************************************************************************************
		*/
		struct SystemManager
		{
			std::vector<std::unique_ptr<System>>	system_database_;	/*!< storage for all the polymorphic systems */
			std::unordered_map<std::string, bool>	system_registered_;	/*!< account for which systems are registered */
			
			unsigned int							number_of_systems_{ 0 };
			struct SystemNameID
			{
				std::string		name_;
				unsigned int	id_;
			};
			std::vector<SystemNameID>				registered_systems_;

			SystemManager();
			/*!
			 * @brief ___JZEngine::ECS::RegisterSystem()___
			 * ****************************************************************************************************
			 * Registers a derived class from System as a system to be processed
			 * by the ECSInstance.
			 * ****************************************************************************************************
			 * @tparam SYSTEM
			 * : The class derived from System to register.
			 * ****************************************************************************************************
			*/
			template <typename SYSTEM>
			void RegisterSystem()
			{
				if (system_registered_.find(typeid(SYSTEM).name()) == system_registered_.end())
				{
					system_database_.emplace_back(std::make_unique<SYSTEM>());
					system_registered_[typeid(SYSTEM).name()] = 1;
					registered_systems_.push_back({ typeid(SYSTEM).name(), number_of_systems_++ });
				}
				else
				{
					std::cout << "WARNING! SystemManager tried to re-register system: " << typeid(SYSTEM).name() << std::endl;
				}
			}

			/*!
			 * @brief ___JZEngine::ECS::Update()___
			 * ****************************************************************************************************
			 * Updates all registered systems with entities that meet
			 * the component signature every frame.
			 * ****************************************************************************************************
			*/
			void Update();

			/*template <typename SYSTEM>
			void RegisterSystem_T()
			{
				using specialtype =  std::tuple_element_t<0, SYSTEM::type>;
				std::cout << typeid(specialtype).name() << std::endl;
			}*/

			template <size_t I = 0, typename...TUPLE>
			typename std::enable_if<I == sizeof...(TUPLE), void>::type
				RegisterTuple(std::tuple<TUPLE...> t)
			{
				// no more tuples to iterate over, return void
				return;
			}

			template <size_t I = 0, typename...TUPLE>
			typename std::enable_if < I < sizeof...(TUPLE), void>::type
				RegisterTuple(std::tuple<TUPLE...> t)
			{
				RegisterSystem<std::tuple_element_t<I, std::tuple<TUPLE...>>>();
				RegisterTuple<I + 1>(t);
			}

			void RegisterConfigSystems();
		};

		/* Forward declare Entity for ECSIntance to get a handle to. */
		struct Entity;
		
		/* ____________________________________________________________________________________________________
		*																				ECSINSTANCE DECLARATION
		   ____________________________________________________________________________________________________*/

		/*!
		 * @brief ___JZEngine::ECS::ECSInstance___
		 * ****************************************************************************************************
		 * Encapsulates the entire ECS, holding one of each
		 * manager. Main interface to the ECS.
		 * ****************************************************************************************************
		*/
		struct ECSInstance // destructor still missing
		{
			ComponentManager	component_manager_;		/*!< holds all registered components  */
			ArchetypeManager	archetype_manager_;		/*!< holds all unique archetypes, i.e. component combinations */
			SystemManager		system_manager_;		/*!< holds all registered systems */

			/*!
			 * @brief ___JZEngine::ECS::ECSInstance::Instance()___
			 * ****************************************************************************************************
			 * Singleton interface.
			 * ****************************************************************************************************
			 * @return ECSInstance&
			 * : A reference to the static ECSInstance.
			 * ****************************************************************************************************
			*/
			static ECSInstance& Instance();

			/*!
			 * @brief ___JZEngine::ECS::ECSInstance::Update()___
			 * ****************************************************************************************************
			 * Calls system manager update which in turns updates
			 * all systems with matching archetypes, i.e. entities.
			 * ****************************************************************************************************
			*/
			void Update();

			/*!
			 * @brief ___JZEngine::ECS::ECSInstance::RegisterComponent()___
			 * ****************************************************************************************************
			 * Registers a struct/class as a component.
			 * ****************************************************************************************************
			 * @tparam COMPONENT
			 * : The struct/class to register as the component.
			 * ****************************************************************************************************
			*/
			template <typename COMPONENT>
			void RegisterComponent()
			{
				component_manager_.RegisterComponent<COMPONENT>();
			}

			/*!
			 * @brief ___JZEngine::ECS::ECSInstance::RegisterSystem()___
			 * ****************************************************************************************************
			 * Registers a derived struct/class from System as an ECS system.
			 * ****************************************************************************************************
			 * @tparam SYSTEM
			 * : The struct/class to register as the system.
			 * ****************************************************************************************************
			*/
			template <typename SYSTEM>
			void RegisterSystem()
			{
				system_manager_.RegisterSystem<SYSTEM>();
			}

			// for debugging purposes
			void Print();

		private:
			/*!
			 * @brief ___JZEngine::ECS::ECSInstance::ECSInstance()___
			 * ****************************************************************************************************
			 * Private constructor to singleton.
			 * ****************************************************************************************************
			*/
			ECSInstance();

			std::vector<Entity> entities_;
		};

		/*!
		 * @brief ___JZEngine::ECS::Chunk::GetComponent()___
		 * ****************************************************************************************************
		 * Get component from a chunk with an entity id.
		 * ****************************************************************************************************
		 * @tparam COMPONENT
		 * : Component to get.
		 * @param id
		 * : id of entity in the chunk.
		 * ****************************************************************************************************
		*/
		template<typename COMPONENT>
		COMPONENT& Chunk::GetComponent(ui32 id)
		{
			assert(("Getting component that does not exist in Entity.",
				owning_archetype_->mask_[ECSInstance::Instance().component_manager_.component_descriptions_<COMPONENT>.bit_] == 1));

			// navigates to location of data
			char* data = data_.get() + (size_t)id * (size_t)owning_archetype_->entity_stride_ +
				(size_t)owning_archetype_->component_stride_[ComponentManager::component_descriptions_<COMPONENT>.bit_];

			// cast to type and return reference
			return *(reinterpret_cast<COMPONENT*>(data));
		}

		/* ____________________________________________________________________________________________________
		*																					ENTITY DECLARATION
		   ____________________________________________________________________________________________________*/

		/*!
		 * @brief ___JZEngine::ECS::Entity___
		 * ****************************************************************************************************
		 * Entity belonging to a chunk with a unique id.
		 * Associated with a combination of components stored
		 * in a chunk.
		 * ****************************************************************************************************
		*/
		struct Entity
		{
			Chunk*								owning_chunk_{ nullptr };	/*!< chunk that holds the components for this entity */
			ubyte								id_{ 255 };					/*!< unique id corresponding to its chunk, i.e. only unique per chunk */
			ui32								ecs_id_;

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
				// calculate ecs_id
				std::cout << owning_chunk_->owning_archetype_->id_ << "," << owning_chunk_->id_ << "," << id_ << std::endl;
				ecs_id_ = owning_chunk_->owning_archetype_->id_ * 1000000 + owning_chunk_->id_ * 1000 + id_;
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

			/*!
			 * @brief ___JZEngine::ECS::Entity::HasComponent()___
			 * ****************************************************************************************************
			 * If the entity has this component. Checked by
			 * the component's unique bit.
			 * ****************************************************************************************************
			 * @param bit
			 * : The bit.
			 * @return 
			 * ****************************************************************************************************
			*/
			bool HasComponent(int bit);

			template <typename COMPONENT>
			bool ComponentRegistered()
			{
				if (!ECSInstance::Instance().component_manager_.ComponentRegistered<COMPONENT>())
				{
					std::cout << "Trying to add unregistered component (" << typeid(COMPONENT).name() << ") to entity." << std::endl;
					return false;
				}
				return true;
			}

			/*!
			 * @brief ___JZEngine::ECS::Entity::AddComponent()___
			 * ****************************************************************************************************
			 * Adds a component to the entity. Changes the component
			 * combination signature, and assigns it a new chunk and
			 * archetype (creating one if need be).
			 * ****************************************************************************************************
			 * @tparam ...COMPONENTS 
			 * : Components to add.
			 * @return Entity&
			 * : This entity.
			 * ****************************************************************************************************
			*/
			template <typename...COMPONENTS>
			Entity& AddComponent()
			{
				// make sure all components are registered
				bool all_registered = true;
				((all_registered = all_registered ? ComponentRegistered<COMPONENTS>() : all_registered), ...);
				if (!all_registered)
				{
					std::cout << "ERROR! Entity::AddComponent - Adding component that is not registered!" << std::endl;
					return *this;
				}

				// check if this entity had a chunk before
				if (owning_chunk_)
				{
					// check if components are already there, if so don't do anything
					bool there = true;
					((there = owning_chunk_->owning_archetype_->mask_[ComponentManager::component_descriptions_<COMPONENTS>.bit_] && there ? true : false), ...);
					if (there)
					{
						return *this;
					}

					// get the archetype of the new combination
					Archetype& new_archetype = ECSInstance::Instance().archetype_manager_.GetArchetype<COMPONENTS...>(owning_chunk_->owning_archetype_->mask_);

					// perform copy of entity over to the new archetype
					ubyte temp_id{ 0 };
					Chunk& temp_chunk = new_archetype.AddEntity(temp_id);

					// deep copy
					//memcpy(temp_chunk.GetDataBegin(temp_id), owning_chunk_->GetDataBegin(id_), owning_chunk_->owning_archetype_->entity_stride_);
					for (int i = 0; i < MAX_COMPONENTS; ++i)
					{
						if (owning_chunk_->owning_archetype_->mask_[i] == 1)
						{
							LoopTupleInitializeComponent(i, &temp_chunk, temp_id, owning_chunk_, id_);
						}
					}

					if (HasComponent(1))
					{
						int ox = owning_chunk_->GetComponent<TestComponent>(id_).x;
						int oy = owning_chunk_->GetComponent<TestComponent>(id_).x;
						int nx = temp_chunk.GetComponent<TestComponent>(temp_id).x;
						int ny = temp_chunk.GetComponent<TestComponent>(temp_id).y;
					}

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

				// change unique ecs_id_
				ecs_id_ = owning_chunk_->owning_archetype_->id_ * 1000000 + owning_chunk_->id_ * 1000 + id_;

				return *this;
			}

			template <size_t I = 0, typename...TUPLE>
			typename std::enable_if<I == sizeof...(TUPLE), void>::type
				LoopTupleInitializeComponent(std::tuple<TUPLE...> t, size_t i, Chunk* newchunk, int newid, Chunk* oldchunk = nullptr, int oldid = -1)
			{
				std::cout << "LoopTupleRender::tuple size exceeded." << std::endl;
				return;
			}

			template <size_t I = 0, typename...TUPLE>
			typename std::enable_if < I < sizeof...(TUPLE), void>::type
				LoopTupleInitializeComponent(std::tuple<TUPLE...> t, size_t i, Chunk* newchunk, int newid, Chunk* oldchunk = nullptr, int oldid = -1)
			{
				if (I == i)
				{
					using COMPONENT = decltype(std::get<I>(t));
					// if there is a previous chunk data to copy
					if (oldchunk)
					{
						newchunk->GetComponent<std::remove_reference_t<COMPONENT>>(newid) = oldchunk->GetComponent<std::remove_reference_t<COMPONENT>>(oldid);
					}
					// else default initialize
					else
					{
						newchunk->GetComponent<std::remove_reference_t<COMPONENT>>(newid) = std::remove_reference_t<COMPONENT>();
					}
					return;
				}
				LoopTupleInitializeComponent<I + 1>(t, i, newchunk, newid, oldchunk, oldid);
			}

			void LoopTupleInitializeComponent(size_t i, Chunk* newchunk, int newid, Chunk* oldchunk = nullptr, int oldid = -1);

			Entity& RemoveComponent(int i);

			//Entity& AddComponent(const ECS::SystemComponents& components);

			/*!
			 * @brief ___JZEngine::ECS::AddComponent()___
			 * ****************************************************************************************************
			 * Adds components to an entity based on the bit id
			 * of the components. Assumes that the used bits are
			 * already registered components.
			 * 
			 * Warning: Does not call the constructors
			 * of the components being added to the entity,
			 * unlike the templated AddComponent().
			 * (will probably change)
			 * ****************************************************************************************************
			 * @param bits 
			 * : bits of the components to add.
			 * @return Entity&
			 * : This entity.
			 * ****************************************************************************************************
			*/
			//template <typename SYSTEM>
			//Entity& AddSystem()
			//{
			//	// check if this entity had a chunk before
			//	if (owning_chunk_)
			//	{
			//		// check if system components are already there, if so don't do anything
			//		bool there = true;
			//		for (auto& c : SYSTEM::components_)
			//		{
			//			if (c == -1)
			//			{
			//				break;
			//			}
			//			if (owning_chunk_->owning_archetype_->mask_[c] != 1)
			//			{
			//				there = false;
			//				break;
			//			}
			//		}
			//		if (there)
			//		{
			//			std::cout << typeid(SYSTEM).name() << " already there." << std::endl;
			//			return *this;
			//		}

			//		// get the archetype of the new combination
			//		Archetype& new_archetype = ECSInstance::Instance().archetype_manager_.GetArchetype(owning_chunk_->owning_archetype_->mask_, SYSTEM::components_);

			//		// perform copy of entity over to the new archetype
			//		ubyte temp_id{ 0 };
			//		Chunk& temp_chunk = new_archetype.AddEntity(temp_id);

			//		// shallow copy
			//		memcpy(temp_chunk.GetDataBegin(temp_id), owning_chunk_->GetDataBegin(id_), owning_chunk_->owning_archetype_->entity_stride_);

			//		//// initialize all components in new chunk
			//		//for (auto& c : SYSTEM::components_)
			//		//{
			//		//	// if old chunk did not have system component, initialize it
			//		//	if (owning_chunk_->owning_archetype_->mask_[c] != 1)
			//		//	{
			//		//		LoopTupleInitializeComponent(ECSConfig::Component(), c, temp_chunk, temp_id);
			//		//	}
			//		//}

			//		// tell old chunk to remove entity
			//		owning_chunk_->RemoveEntity(id_);

			//		// update owning_chunk and id
			//		owning_chunk_ = &temp_chunk;
			//		id_ = temp_id;
			//	}
			//	else
			//	{
			//		// get the new archetype based on this entities component combination
			//		Archetype& new_archetype = ECSInstance::Instance().archetype_manager_.GetArchetype(SYSTEM::components_);

			//		// add this new entity to the archetype
			//		owning_chunk_ = &new_archetype.AddEntity(id_);

			//		// initialize all components in new chunk
			//		for (int i = 0; i < MAX_COMPONENTS; ++i)
			//		{
			//			if (owning_chunk_->owning_archetype_->mask_[i] == 1)
			//			{
			//				LoopTupleInitializeComponent(ECSConfig::Component(), i, owning_chunk_, id_);
			//			}
			//		}
			//	}

			//	// change unique ecs_id_
			//	ecs_id_ = owning_chunk_->owning_archetype_->id_ * 1000000 + owning_chunk_->id_ * 1000 + id_;

			//	return *this;
			//}

			Entity& AddSystem(int systemid);

			/*template <typename...SYSTEMS>
			Entity& AddSystems()
			{
				((AddSystem<SYSTEMS>()), ...);
				return  *this;
			}*/
		};

		/* ____________________________________________________________________________________________________
		*																					SYSTEM DECLARATION
		   ____________________________________________________________________________________________________*/

		/*!
		 * @brief ___JZEngine::ECS::System___
		 * ****************************************************************************************************
		 * Holds the logic to update entities with required
		 * components. E.g. A Movement System might require
		 * an entity having a Position component, all entities
		 * with a position component will be updated by such a system.
		 * ****************************************************************************************************
		*/
		struct System
		{
			ubyte							current_id_{ 0 };			/*!< current entity id of the component being updated */
			Chunk*							current_chunk_{ nullptr };	/*!< current chunk the entity being updated belongs to */
			std::bitset<MAX_COMPONENTS>		mask_;						/*!< component mask of the system, to decide which entities to update */
			ui32							number_of_components_{ 0 };	/*!< number of components*/

			JZEngine::ECS::SystemComponents components_;

			System() {}
			virtual ~System() = default;

			/*!
			 * @brief ___JZEngine::ECS::System::RegisterComponents()___
			 * ****************************************************************************************************
			 * Registers all components as a precautionary measure.
			 * Sets the mask and component signature for the derived system.
			 * Component signature in the derived is needed to support
			 * adding of components based on systems to the entities.
			 * ****************************************************************************************************
			 * @tparam COMPONENTS
			 * : Components to add.
			 * @param components
			 * : Component signature container passed in from the derived.
			 * ****************************************************************************************************
			*/
			template <typename...COMPONENTS>
			void RegisterComponents()
			{
				// register all components
				//((ECSInstance::Instance().component_manager_.RegisterComponent<COMPONENTS>()), ...);
				// create mask
				((mask_[ComponentManager::component_descriptions_<COMPONENTS>.bit_] = 1), ...);
				// fill components with max value
				components_.fill(-1);
				((components_[number_of_components_++] = ComponentManager::component_descriptions_<COMPONENTS>.bit_), ...);
			}

			/*!
			 * @brief ___JZEngine::ECS::System::GetComponent()___
			 * ****************************************************************************************************
			 * Gets a component from the current entity being processed.
			 * ****************************************************************************************************
			 * @tparam COMPONENT
			 * : Component to get.
			 * @return Component&
			 * : Reference to the component.
			 * ****************************************************************************************************
			*/
			template <typename COMPONENT>
			COMPONENT& GetComponent()
			{
				assert(current_chunk_);
				return current_chunk_->GetComponent<COMPONENT>(current_id_);
			}

			/*!
			 * @brief ___JZEngine::ECS::System::FrameBegin()___
			 * ****************************************************************************************************
			 * Virtual function, called only once per frame
			 * for each system.
			 * ****************************************************************************************************
			*/
			virtual void FrameBegin() { };

			/*!
			 * @brief ___JZEngine::ECS::System::Update()___
			 * ****************************************************************************************************
			 * Virtual function, called once for each entity per frame.
			 * ****************************************************************************************************
			*/
			virtual void Update(const float& dt) = 0;
		};
	}
}