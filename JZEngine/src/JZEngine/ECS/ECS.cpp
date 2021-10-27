/*	__FILE HEADER__
*	File:		ECS.cpp
	Primary:	Zachary Tay
	Date:		26/08/21
	Brief:		Contains all ECS logic:
				Entity, EntityManager, Component, ComponentManager,
				Archetype, ArchetypeManager, System, SystemManager,
				ECSInstance Singleton.

				Exposes the ECS through an ECSInstance singleton.
*/

#include "ECS.h"
#include "ECSconfig.h"
#include "../DebugTools/PerformanceData.h"

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
		ComponentManager::ComponentManager(ECSInstance* ecs)
			:
			ecs_instance_(ecs)
		{
			RegisterConfigComponents();
		}

		ComponentManager::~ComponentManager()
		{}

		template <typename COMPONENT>
		ComponentDescription ComponentManager::component_descriptions_ =
			ComponentDescription( sizeof(COMPONENT), -1, typeid(COMPONENT).name());

		void ComponentManager::RegisterConfigComponents()
		{
			RegisterTuple(ECSConfig::Component());
		}

		/* ____________________________________________________________________________________________________
		*																					CHUNK DEFINITION
		   ____________________________________________________________________________________________________*/

		Chunk::Chunk()
		{
		}

		Chunk::~Chunk()
		{
			/*if (data_)
			{
				delete[] data_;
			}*/
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
		void Chunk::Initialize(Archetype* owner, ui32 id)
		{
			id_ = id;
			// set owner
			owning_archetype_ = owner;
			// get handle to ecs instance
			ecs_instance_ = owning_archetype_->ecs_instance_;
			// initializes data
			//data_ = new char[owning_archetype_->entity_stride_ * ENTITIES_PER_CHUNK];
			data_ = std::make_unique<char[]>(owning_archetype_->entity_stride_ * ENTITIES_PER_CHUNK);
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
			char* entity_data = data_.get() + (size_t)id * (size_t)owning_archetype_->entity_stride_;
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
			memset(data_.get(), 0, (size_t)owning_archetype_->entity_stride_ * (size_t)ENTITIES_PER_CHUNK);
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
			return data_.get() + (size_t)id * (size_t)owning_archetype_->entity_stride_;
		}

		void Chunk::Print()
		{
			// print visual description of chunk
			std::cout << "Chunk Entities: ";
			for (int i = 0; i < number_of_entities_; ++i)
			{
				if (active_flags_[i])
				{
					std::cout << "o";
				}
				else
				{
					std::cout << "x";
				}
			}
			std::cout << std::endl << "Free IDS: ";
			for (int i = 0; i < free_ids_count_; ++i)
			{
				std::cout << i << ",";
			}
			std::cout << std::endl << "Entity Addresses: " << std::endl;
			for (int i = 0; i < number_of_entities_; ++i)
			{
				std::cout << "Entity " << i << ". " << static_cast<void*>(GetDataBegin(static_cast<ubyte>(i))) << std::endl;
			}
		}

		/* ____________________________________________________________________________________________________
		*																				ARCHETYPE DEFINITION
		   ____________________________________________________________________________________________________*/

		Archetype::Archetype(ECSInstance* ecs)
			:
			ecs_instance_(ecs)
		{
			component_stride_.fill(static_cast<ui16>(-1));
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
			ecs_instance_ = archetype.ecs_instance_;
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
		void Archetype::Initialize(ui32 id, ECSInstance* ecs)
		{
			ecs_instance_ = ecs;
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
			entity_stride_ += ecs_instance_->component_manager_.component_sizes_[bit];
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
				if (chunk_database_[i].number_of_entities_ < ENTITIES_PER_CHUNK || chunk_database_[i].free_ids_count_ > 0)
				{
					id = chunk_database_[i].AddEntity();
					return chunk_database_[i];
				}
			}
			// add new chunk
			if (number_of_chunks_ < chunk_database_.max_size())
			{
				chunk_database_[number_of_chunks_].Initialize(this, number_of_chunks_);
				id = chunk_database_[number_of_chunks_].AddEntity();
				return chunk_database_[number_of_chunks_++];
			}
			// else game breaking error
			std::cout << "ERROR! Not enough chunks to support entities of type!" << std::endl;
			return chunk_database_[0];
		}

		void Archetype::Print()
		{
			// print information
			std::cout << "ARCHETYPE " << id_ << std::endl;
			std::cout << "__________________________________________" << std::endl;
			std::cout << "Mask: " << mask_.to_string() << std::endl;
			std::cout << "Entity Stride: " << entity_stride_ << std::endl;
			std::cout << "------Strides: ";
			for (int i = MAX_COMPONENTS-1; i >= 0; --i)
			{
				if (component_stride_[i] < static_cast<ui16>(-1))
				{
					std::cout << component_stride_[i] << ",";
				}
			}
			std::cout << std::endl << std::endl;

			for (ui32 i = 0; i < number_of_chunks_; ++i)
			{
				std::cout << "CHUNK " << i << std::endl;
				std::cout << "____________________" << std::endl;
				chunk_database_[i].Print();
				std::cout << "____________________" << std::endl;
				std::cout << std::endl;
			}

			std::cout << "__________________________________________" << std::endl;
		}

		/* ____________________________________________________________________________________________________
		*																		ARCHETYPE MANAGER DEFINITION
		   ____________________________________________________________________________________________________*/

		ArchetypeManager::ArchetypeManager(ECSInstance* ecs)
			:
			ecs_instance_(ecs)
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
		Archetype& ArchetypeManager::GetArchetype(const std::array<ui32, MAX_COMPONENTS>& bits)
		{
			// create mask
			std::bitset<MAX_COMPONENTS> mask;

			for (auto& b : bits)
			{
				if (b == -1)
				{
					break;
				}
				mask[b] = 1;
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
			archetype_database_[number_of_archetypes_].Initialize(number_of_archetypes_, ecs_instance_);
			archetype_exist_tracker_[mask] = number_of_archetypes_;

			// register all components into it
			for (auto& b : bits)
			{
				if (b == -1)
				{
					break;
				}
				archetype_database_[number_of_archetypes_].RegisterComponent(b);
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
		Archetype& ArchetypeManager::GetArchetype(const std::bitset<MAX_COMPONENTS>& currentmask, const std::array<ui32, MAX_COMPONENTS>& bits)
		{
			// if currentmask is empty, create new archetype from new components
			if (currentmask.none())
			{
				return GetArchetype(bits);
			}
			// build new mask
			std::bitset<MAX_COMPONENTS> new_mask = currentmask;
			for (auto& b : bits)
			{
				if (b == -1)
				{
					break;
				}
				new_mask[b] = 1;
			}
			// check if archetype already exists
			if (archetype_exist_tracker_.find(new_mask) != archetype_exist_tracker_.end())
			{
				return archetype_database_[archetype_exist_tracker_[new_mask]];
			}
			// else copy archetype and add components
			archetype_database_[number_of_archetypes_] = archetype_database_[archetype_exist_tracker_[currentmask]];
			Archetype& new_archetype = archetype_database_[number_of_archetypes_];
			for (auto& b : bits)
			{
				if (b == -1)
				{
					break;
				}
				if (new_archetype.mask_[b] != 1)
				{
					new_archetype.RegisterComponent(b);
				}
			}
			new_archetype.id_ = number_of_archetypes_;
			archetype_exist_tracker_[new_archetype.mask_] = number_of_archetypes_;
			++number_of_archetypes_;
			return new_archetype;
		}

		void ArchetypeManager::Print()
		{
			for (ui32 i = 0; i < number_of_archetypes_; ++i)
			{
				archetype_database_[i].Print();
			}
		}

		/* ____________________________________________________________________________________________________
		*																					SYSTEM DEFINITION
		   ____________________________________________________________________________________________________*/

		SystemManager::SystemManager(ECSInstance* ecs)
			:
			ecs_instance_(ecs)
		{
			RegisterConfigSystems();
		}

		SystemManager::~SystemManager()
		{

		}

		/*!
		* @brief ___JZEngine::ECS::Update()___
		* ****************************************************************************************************
		* Updates all registered systems with entities that meet
		* the component signature every frame.
		* ****************************************************************************************************
		*/
		void SystemManager::Update(float dt)
		{
			ArchetypeManager& am = ecs_instance_->archetype_manager_;
			for (auto& system : system_database_)
			{
				PerformanceData::StartMark(system->name_, PerformanceData::TimerType::ECS_SYSTEMS);
				system->FrameBegin(dt);
				for (ui32 j = 0; j < am.number_of_archetypes_; ++j)
				{
					// if system mask matches archetype mask, means archetype holds entities of interest
					if ((system->mask_ & am.archetype_database_[j].mask_) == system->mask_)
					{
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
									system->Update(dt);
								}
							}
						}
					}
				}
				system->FrameEnd(dt);
				PerformanceData::EndMark(system->name_, PerformanceData::TimerType::ECS_SYSTEMS);
			}
		}

		void SystemManager::RegisterConfigSystems()
		{
			RegisterTuple(ECSConfig::System());
		}

		EntityManager::EntityManager(ECSInstance* ecs)
			:
			ecs_instance_(ecs)
		{
			entities_.reserve(ENTITIES_RESERVE);
		}

		EntityManager::~EntityManager()
		{

		}

		ui32 EntityManager::CreateEntity(ui32 parent)
		{
			if (parent != -1)
			{
				if (!entities_[parent].HasChildSpace())
				{
					return static_cast<ui32>(-1);
				}
			}
			ui32 id{ 0 };
			if (free_entity_slots_.empty())
			{
				id = entity_count_;
				/*if (entity_count_ > 256)
				{
					int i = 0;
				}*/
				entities_.push_back(Entity(ecs_instance_, entity_count_++, parent));
			}
			else
			{
				id = free_entity_slots_.top();
				entities_[free_entity_slots_.top()] = Entity(ecs_instance_, free_entity_slots_.top(), parent);
				free_entity_slots_.pop();
			}
			if (parent != -1)
			{
				// add this newly created entity as child to parent
				if (!entities_[parent].AddChild(id))
				{
					std::cout << "ECS::ENTITYMANAGER::entity of entity_id_ " << parent << " cannot accept any more children." << std::endl;
				}
			}
			else
			{
				if (free_root_slots_.empty())
				{
					root_ids_.push_back(id);
					entities_[id].root_id_ = root_count_++;
				}
				else
				{
					root_ids_[free_root_slots_.top()] = id;
					entities_[id].root_id_ = free_root_slots_.top();
					free_root_slots_.pop();
				}
			}
			return id;
		}

		void EntityManager::RemoveEntity(ui32 entity)
		{
			entities_[entity].ResetEntity();
			//free_entity_slots_.push(entity);
		}

		Entity& EntityManager::GetEntity(ui32 id)
		{
			assert(id < entities_.size());
			return entities_[id];
		}

		/* ____________________________________________________________________________________________________
		*																				ECSINSTANCE DEFINITION
		   ____________________________________________________________________________________________________*/

		ECSInstance::ECSInstance()
			:
			component_manager_(this),
			archetype_manager_(this),
			system_manager_(this),
			entity_manager_(this)
		{
		}

		/*!
		 * @brief ___JZEngine::ECS::ECSInstance::Update()___
		 * ****************************************************************************************************
		 * Calls system manager update which in turns updates
		 * all systems with matching archetypes, i.e. entities.
		 * ****************************************************************************************************
		*/
		void ECSInstance::Update(float dt)
		{
			system_manager_.Update(dt);
		}

		ui32 ECSInstance::CreateEntity(ui32 parent)
		{
			return entity_manager_.CreateEntity(parent);
		}

		void ECSInstance::RemoveEntity(ui32 entity)
		{
			entity_manager_.RemoveEntity(entity);
		}

		Entity& ECSInstance::GetEntity(ui32 id)
		{
			return entity_manager_.GetEntity(id);
		}

		void ECSInstance::Print()
		{
			std::cout << "______________________________________________________________________" << std::endl;
			std::cout << "PRINTING ECS" << std::endl << std::endl;
			archetype_manager_.Print();
			std::cout << "______________________________________________________________________" << std::endl;
		}

		Entity::Entity(ECSInstance* ecs)
			:
			ecs_instance_(ecs),
			ecs_id_(static_cast<ui32>(-1)),
			entity_id_(static_cast<ui32>(-1)),
			parent_(static_cast<ui32>(-1))
		{
			children_.fill(static_cast<ui32>(-1));
		}

		Entity::Entity(ECSInstance* ecs, ui32 entityid, ui32 parent)
			:
			ecs_instance_(ecs),
			entity_id_(entityid),
			parent_(parent),
			ecs_id_(static_cast<ui32>(-1))
		{
			children_.fill(static_cast<ui32>(-1));
		}

		Entity::~Entity()
		{

		}

		void Entity::ResetEntity()
		{
			// Reset all children entities
			for (auto& child : children_)
			{
				if (child != -1)
				{
					ecs_instance_->GetEntity(child).ResetEntity();
				}
			}
			// remove entity from chunk
			if (owning_chunk_)
			{
				owning_chunk_->RemoveEntity(id_);
				owning_chunk_ = nullptr;
			}
			// remove self from parent entity
			if (parent_ != -1)
			{
				ecs_instance_->entity_manager_.entities_[parent_].RemoveChild(entity_id_);
			}
			// if entity was a root, remove from root
			if (root_id_ != -1)
			{
				ecs_instance_->entity_manager_.root_ids_[root_id_] = static_cast<ui32>(-1);
				ecs_instance_->entity_manager_.free_root_slots_.push(root_id_);
			}
			// set id to be used again by entity manager
			ecs_instance_->entity_manager_.free_entity_slots_.push(entity_id_);
			// reset member variables
			root_id_	= static_cast<ui32>(-1);
			entity_id_	= static_cast<ui32>(-1);
			parent_		= static_cast<ui32>(-1);
			id_			= static_cast<ubyte>(255);
			ecs_id_		= static_cast<ui32>(-1);;
			children_count_ = 0;
			children_before_ = 0;
			children_.fill(static_cast<ui32>(-1));
		}
		
		bool Entity::AddChild(ui32 childId)
		{
			if (children_before_ < ENTITY_MAX_CHILDREN)
			{
				children_[children_before_++] = childId;
				++children_count_;
				return true;
			}
			else
			{
				for (auto& c : children_)
				{
					if (c == -1)
					{
						c = childId;
						++children_count_;
						return true;
					}
				}
			}
			return false;
		}

		void Entity::RemoveChild(ui32 childId)
		{
			for (auto& c : children_)
			{
				if (c != -1)
				{
					if (c == childId)
					{
						c = static_cast<ui32>(-1);
						--children_count_;
					}
				}
			}
		}

		bool Entity::HasChildSpace()
		{
			if (children_before_ < ENTITY_MAX_CHILDREN)
			{
				return true;
			}
			else
			{
				for (auto& child : children_)
				{
					if (child == -1)
					{
						return true;
					}
				}
			}
			return false;
		}

		bool Entity::HasComponent(int bit)
		{
			if (owning_chunk_)
			{
				return owning_chunk_->owning_archetype_->mask_[bit] == 1;
			}
			return false;
		}

		Entity& Entity::AddComponent(ui32 bit)
		{
			LoopTupleAddComponent(ECSConfig::Component(), bit);
			return *this;
		}

		void Entity::LoopTupleInitializeComponent(size_t i, Chunk* newchunk, int newid, Chunk* oldchunk, int oldid)
		{
			LoopTupleInitializeComponent(ECSConfig::Component(), i, newchunk, newid, oldchunk, oldid);
		}

		Entity& Entity::RemoveComponent(int bit)
		{
			// if no entities
			if (!owning_chunk_)
			{
				std::cout << "JZEngine::Entity::Trying to remove component from entity that does not have components." << std::endl;
				return *this;
			}
			// if entity does not have this component
			if (owning_chunk_->owning_archetype_->mask_[bit] != 1)
			{
				std::cout << "JZEngine::Entity::Trying to remove unexisting component from entity." << std::endl;
				return *this;
			}

			SystemComponents components;
			components.fill(static_cast<ui32>(-1));
			int count{ 0 };
			for (int i = 0; i < MAX_COMPONENTS; ++i)
			{
				if (owning_chunk_->owning_archetype_->mask_[i] == 1 && i != bit)
				{
					components[count++] = i;
				}
			}

			// get the new archetype based on this entities component combination
			Archetype& new_archetype = ecs_instance_->archetype_manager_.GetArchetype(components);
			ubyte temp_id;
			Chunk* temp_chunk = &new_archetype.AddEntity(temp_id);

			// copy old data from old chunk into new chunk
			for (int i = 0; i < MAX_COMPONENTS; ++i)
			{
				if (temp_chunk->owning_archetype_->mask_[i] == 1)
				{
					LoopTupleInitializeComponent(ECSConfig::Component(), i, temp_chunk, temp_id, owning_chunk_, id_);
				}
			}

			// tell old chunk to remove entity
			owning_chunk_->RemoveEntity(id_);

			// update owning_chunk and id
			owning_chunk_ = temp_chunk;
			id_ = temp_id;

			// change unique ecs_id_
			ecs_id_ = owning_chunk_->owning_archetype_->id_ * 1000000 + owning_chunk_->id_ * 1000 + id_;

			return *this;
		}

		Entity& Entity::AddSystem(int systemid)
		{
			const SystemComponents& components = ecs_instance_->system_manager_.system_database_[systemid]->components_;
			// check if this entity had a chunk before
			if (owning_chunk_)
			{
				// check if system components are already there, if so don't do anything
				bool there = true;
				for (auto& c : components)
				{
					if (c == -1)
					{
						break;
					}
					if (owning_chunk_->owning_archetype_->mask_[c] != 1)
					{
						there = false;
						break;
					}
				}
				if (there)
				{
					//std::cout << typeid(SYSTEM).name() << " already there." << std::endl;
					return *this;
				}

				// get the archetype of the new combination
				Archetype& new_archetype = ecs_instance_->archetype_manager_.GetArchetype(owning_chunk_->owning_archetype_->mask_, components);

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

				// initialize all components in new chunk
				for (auto& c : components)
				{
					if (c == -1)
					{
						break;
					}
					// if old chunk did not have system component, initialize it
					if (owning_chunk_->owning_archetype_->mask_[c] != 1)
					{
						LoopTupleInitializeComponent(ECSConfig::Component(), c, &temp_chunk, temp_id);
					}
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
				Archetype& new_archetype = ecs_instance_->archetype_manager_.GetArchetype(components);

				// add this new entity to the archetype
				owning_chunk_ = &new_archetype.AddEntity(id_);

				// initialize all components in new chunk
				for (int i = 0; i < MAX_COMPONENTS; ++i)
				{
					if (owning_chunk_->owning_archetype_->mask_[i] == 1)
					{
						LoopTupleInitializeComponent(ECSConfig::Component(), i, owning_chunk_, id_);
					}
				}
			}

			// change unique ecs_id_
			ecs_id_ = owning_chunk_->owning_archetype_->id_ * 1000000 + owning_chunk_->id_ * 1000 + id_;

			return *this;
		}

		//Entity& Entity::AddComponent(const ECS::SystemComponents& components)
		//{
		//	// check if this entity had a chunk before
		//	if (owning_chunk_)
		//	{
		//		// check if system components are already there, if so don't do anything
		//		bool there = true;
		//		for (auto& c : components)
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
		//			std::cout << "system components are already there." << std::endl;
		//			return *this;
		//		}

		//		// get the archetype of the new combination
		//		Archetype& new_archetype = ECSInstance::Instance().archetype_manager_.GetArchetype(owning_chunk_->owning_archetype_->mask_, components);

		//		// perform copy of entity over to the new archetype
		//		ubyte temp_id{ 0 };
		//		Chunk& temp_chunk = new_archetype.AddEntity(temp_id);

		//		// shallow copy
		//		memcpy(temp_chunk.GetDataBegin(temp_id), owning_chunk_->GetDataBegin(id_), owning_chunk_->owning_archetype_->entity_stride_);

		//		// tell old chunk to remove entity
		//		owning_chunk_->RemoveEntity(id_);

		//		// update owning_chunk and id
		//		owning_chunk_ = &temp_chunk;
		//		id_ = temp_id;
		//	}
		//	else
		//	{
		//		// get the new archetype based on this entities component combination
		//		Archetype& new_archetype = ECSInstance::Instance().archetype_manager_.GetArchetype(components);

		//		// add this new entity to the archetype
		//		owning_chunk_ = &new_archetype.AddEntity(id_);
		//	}

		//	// change unique ecs_id_
		//	ecs_id_ = owning_chunk_->owning_archetype_->id_ * 1000000 + owning_chunk_->id_ * 1000 + id_;

		//	return *this;
		//}
	}
}