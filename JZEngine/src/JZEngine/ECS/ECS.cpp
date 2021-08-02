#include "ECS.h"

#include <iostream>

namespace JZEngine
{
	namespace ECS
	{
		/* ____________________________________________________________________________________________________
		*																	COMPONENT DESCRIPTION DEFINITION
		   ____________________________________________________________________________________________________*/

		/*!
		* @brief ___JZEngine::ECS::ComponentDescription___
		* ****************************************************************************************************
		* What defines an ecs component. Byte size, unique bit id,
		* and a unique name. All registered components will have
		* features defined by these data members.
		* ****************************************************************************************************
		*/
		ComponentDescription::ComponentDescription(ui32 size, ui32 bit, std::string name)
			:
			size_(size),
			bit_(bit),
			name_(name)
		{

		}

		/* ____________________________________________________________________________________________________
		*																		COMPONENT MANAGER DEFINITION
		   ____________________________________________________________________________________________________*/

		/*!
		* @brief ___JZEngine::ECS::ComponentManager___
		* ****************************************************************************************************
		* Holds all component descriptions and provides these
		* details to other parts of the ECS system when called
		* upon.
		* ****************************************************************************************************
		*/
		ComponentManager::ComponentManager()
		{

		}

		ComponentManager::~ComponentManager()
		{

		}

		template <typename COMPONENT>
		ComponentDescription ComponentManager::component_descriptions_ =
			ComponentDescription( sizeof(COMPONENT), -1, typeid(COMPONENT).name());

		/* ____________________________________________________________________________________________________
		*																					CHUNK DEFINITION
		   ____________________________________________________________________________________________________*/

		Chunk::Chunk()
		{
		}

		Chunk::~Chunk()
		{
			if (data_)
			{
				delete[] data_;
			}
		}

		/*!
		 * @brief ___JZEngine::ECS::Chunk::Initialize()___
		 * ****************************************************************************************************
		 * Sets the owning archetype of the chunk and allocates data_ bytes.
		 * ****************************************************************************************************
		 * @param owner
		 * : Pointer to the owning archetype object.
		 * ****************************************************************************************************
		*/
		void Chunk::Initialize(Archetype* owner)
		{
			// set owner
			owning_archetype_ = owner;
			// initializes data
			data_ = new char[owning_archetype_->entity_stride_ * ENTITIES_PER_CHUNK];
		}

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
		ubyte Chunk::AddEntity()
		{
			// check if free ids stack has any to give
			if (free_ids_count_ <= 0)
			{
				active_flags_[number_of_entities_] = 1;
				return number_of_entities_++;
			}

			// if there are free ids
			ubyte id = free_ids_[--free_ids_count_];

			// set entity flag at that id to active and return
			active_flags_[id] = 1;
			return id;
		}

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
		void Chunk::RemoveEntity(ubyte id)
		{
			active_flags_[id] = 0;
			ZeroEntityData(id);
			free_ids_[free_ids_count_++] = id;
		}

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
		void Chunk::ZeroEntityData(ubyte id)
		{
			// get location of entity data
			char* entity_data = data_ + (size_t)id * (size_t)owning_archetype_->entity_stride_;
			// sets to 0
			memset(entity_data, 0, (size_t)owning_archetype_->entity_stride_);
		}

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
		void Chunk::ZeroAllData()
		{
			memset(data_, 0, (size_t)owning_archetype_->entity_stride_ * (size_t)ENTITIES_PER_CHUNK);
		}

		/*!
		 * @brief ___IsFull___
		 * ****************************************************************************************************
		 * @return bool
		 * : If the chunk is full.
		 * ****************************************************************************************************
		*/
		bool Chunk::IsFull()
		{
			return (free_ids_count_ == 0 && number_of_entities_ >= ENTITIES_PER_CHUNK);
		}

		/*!
		 * @brief ___JZEngine::ECS::Chunk::GetDataBegin()___
		 * ****************************************************************************************************
		 * Gets the start of memory of an entity.
		 * ****************************************************************************************************
		*/
		char* Chunk::GetDataBegin(ubyte id)
		{
			return data_ + (size_t)id * (size_t)owning_archetype_->entity_stride_;
		}

		/* ____________________________________________________________________________________________________
		*																				ARCHETYPE DEFINITION
		   ____________________________________________________________________________________________________*/

		Archetype::Archetype()
		{
		}

		Archetype::~Archetype()
		{

		}

		/*!
		 * @brief ___JZEngine::ECS::Archetype::operator=()___
		 * ****************************************************************************************************
		 * Only copies entity_stride_, mask_, and component_stride_.
		 * Mainly used to create a new archetype that this archetype's
		 * description if a subset of.
		 * ****************************************************************************************************
		*/
		Archetype& Archetype::operator=(const Archetype& archetype)
		{
			entity_stride_ = archetype.entity_stride_;
			mask_ = archetype.mask_;
			component_stride_ = archetype.component_stride_;
			return *this;
		}

		/*!
		 * @brief ___JZEngine::ECS::Archetype::Initialize()___
		 * ****************************************************************************************************
		 * Sets the unique id of this archetype.
		 * ****************************************************************************************************
		 * @param id
		 * : Unique id to set.
		 * ****************************************************************************************************
		*/
		void Archetype::Initialize(ui32 id)
		{
			id_ = id;
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
		void Archetype::RegisterComponent(ui32 bit)
		{
			mask_[bit] = 1;
			component_stride_[bit] = entity_stride_;
			entity_stride_ += ECSInstance::Instance().component_manager_.component_sizes_[bit];
		}

		/*!
		 * @brief ___JZEngine::ECS::Archetype::AddEntity()___
		 * ****************************************************************************************************
		 * Adds an entity into one of the chunks stored in this archetype. If
		 * no chunks with available space, create a new chunk.
		 * ****************************************************************************************************
		*/
		Chunk& Archetype::AddEntity(ubyte& id)
		{
			// check if there are any empty chunks
			for (ui32 i = 0; i < number_of_chunks_; ++i)
			{
				if (chunk_database_[i].number_of_entities_ < ENTITIES_PER_CHUNK)
				{
					id = chunk_database_[i].AddEntity();
					return chunk_database_[i];
				}
			}
			// add new chunk
			if (number_of_chunks_ < chunk_database_.max_size())
			{
				chunk_database_[number_of_chunks_].Initialize(this);
			}
			id = chunk_database_[number_of_chunks_].AddEntity();
			return chunk_database_[number_of_chunks_++];
		}

		/* ____________________________________________________________________________________________________
		*																		ARCHETYPE MANAGER DEFINITION
		   ____________________________________________________________________________________________________*/

		ArchetypeManager::ArchetypeManager()
		{

		}

		ArchetypeManager::~ArchetypeManager()
		{

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
		Archetype& ArchetypeManager::GetArchetype(const std::array<ui32, MAX_COMPONENTS>& bits, ui32 count)
		{
			// create mask
			std::bitset<MAX_COMPONENTS> mask;

			for (int i = 0; i < count; ++i)
			{
				mask[bits[i]] = 1;
			}

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
			for (int i = 0; i < count; ++i)
			{
				archetype_database_[number_of_archetypes_].RegisterComponent(bits[i]);
			}

			return archetype_database_[number_of_archetypes_++];
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
		Archetype& ArchetypeManager::GetArchetype(const std::bitset<MAX_COMPONENTS>& currentmask, const std::array<ui32, MAX_COMPONENTS>& bits, ui32 count)
		{
			// if currentmask is empty, create new archetype from new components
			if (currentmask.none())
			{
				return GetArchetype(bits, count);
			}
			// build new mask
			std::bitset<MAX_COMPONENTS> new_mask = currentmask;
			for (int i = 0; i < count; ++i)
			{
				new_mask[bits[i]] = 1;
			}
			// check if archetype already exists
			if (archetype_exist_tracker_.find(new_mask) != archetype_exist_tracker_.end())
			{
				return archetype_database_[archetype_exist_tracker_[new_mask]];
			}
			// else copy archetype and add components
			archetype_database_[number_of_archetypes_] = archetype_database_[archetype_exist_tracker_[currentmask]];
			Archetype& new_archetype = archetype_database_[number_of_archetypes_];
			for (int i = 0; i < count; ++i)
			{
				new_archetype.RegisterComponent(bits[i]);
			}
			new_archetype.id_ = number_of_archetypes_;
			archetype_exist_tracker_[new_archetype.mask_] = number_of_archetypes_;
			++number_of_archetypes_;
			return new_archetype;
		}

		/* ____________________________________________________________________________________________________
		*																					SYSTEM DEFINITION
		   ____________________________________________________________________________________________________*/

		/*!
		* @brief ___JZEngine::ECS::Update()___
		* ****************************************************************************************************
		* Updates all registered systems with entities that meet
		* the component signature every frame.
		* ****************************************************************************************************
		*/
		void SystemManager::Update()
		{
			const float dt = 1.0f;
			ArchetypeManager& am = ECSInstance::Instance().archetype_manager_;
			for (auto& system : system_database_)
			{
				for (ui32 j = 0; j < am.number_of_archetypes_; ++j)
				{
					// if system mask matches archetype mask, means archetype holds entities of interest
					if ((system->mask_ & am.archetype_database_[j].mask_) == system->mask_)
					{
						system->FrameBegin();
						// loop through archetype chunks
						for (ui32 h = 0; h < am.archetype_database_[j].number_of_chunks_; ++h)
						{
							system->current_chunk_ = &am.archetype_database_[j].chunk_database_[h];
							// for each entity in a chunk
							for (ubyte i = 0; i < system->current_chunk_->number_of_entities_; ++i)
							{
								// if it is marked active, i.e. exists 
								if (system->current_chunk_->active_flags_[i])
								{
									system->current_id_ = i;
									system->Update(1.0f);
								}
							}
						}
					}
				}
			}
		}

		/* ____________________________________________________________________________________________________
		*																				ECSINSTANCE DEFINITION
		   ____________________________________________________________________________________________________*/

		ECSInstance::ECSInstance()
		{
		}

		/*!
		 * @brief ___JZEngine::ECS::ECSInstance::Instance()___
		 * ****************************************************************************************************
		 * Singleton interface.
		 * ****************************************************************************************************
		 * @return ECSInstance&
		 * : A reference to the static ECSInstance.
		 * ****************************************************************************************************
		*/
		ECSInstance& ECSInstance::Instance()
		{
			static ECSInstance instance;
			return instance;
		}

		/*!
		 * @brief ___JZEngine::ECS::ECSInstance::Update()___
		 * ****************************************************************************************************
		 * Calls system manager update which in turns updates
		 * all systems with matching archetypes, i.e. entities.
		 * ****************************************************************************************************
		*/
		void ECSInstance::Update()
		{
			system_manager_.Update();
		}

		Entity::Entity()
		{

		}

		Entity::~Entity()
		{

		}
	}
}