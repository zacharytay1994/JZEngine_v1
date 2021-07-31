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

		Archetype::Archetype()
		{
		}

		/*Archetype::Archetype(const Archetype& archetype)
			:
			entity_stride_(archetype.entity_stride_),
			mask_(archetype.mask_)
		{

		}*/

		Archetype::~Archetype()
		{

		}

		Archetype& Archetype::operator=(const Archetype& archetype)
		{
			entity_stride_ = archetype.entity_stride_;
			mask_ = archetype.mask_;
			component_stride_ = archetype.component_stride_;
			return *this;
		}

		void Archetype::Initialize(ui32 id)
		{
			id_ = id;
		}

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

		char* Chunk::GetDataBegin(ubyte id)
		{
			return data_ + (size_t)id * (size_t)owning_archetype_->entity_stride_;
		}

		ArchetypeManager::ArchetypeManager()
		{

		}

		ArchetypeManager::~ArchetypeManager()
		{

		}

		Entity::Entity()
		{

		}

		Entity::~Entity()
		{

		}

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

		ECSInstance::ECSInstance()
		{
			component_manager_.RegisterComponent<TestData>();
			component_manager_.RegisterComponent<TestData2>();
			/*std::cout << "TestData2: " << ComponentManager::component_descriptions_<TestData>.name_ << std::endl;
			std::cout << "Bit: " << ComponentManager::component_descriptions_<TestData>.bit_ << std::endl;
			std::cout << "Size: " << ComponentManager::component_descriptions_<TestData>.size_ << std::endl;
			std::cout << sizeof(archetype_manager_) << std::endl;*/
		}

		ECSInstance& ECSInstance::Instance()
		{
			static ECSInstance instance;
			return instance;
		}

		void ECSInstance::Update()
		{
			system_manager_.Update();
		}
	}
}