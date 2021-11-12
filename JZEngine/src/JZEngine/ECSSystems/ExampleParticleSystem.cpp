#include <PCH.h>
#include "ExampleParticleSystem.h"
#include "../ECS/ECSConfig.h"
#include "../Resource/ObjectPool.h"

namespace JZEngine
{
	ExampleParticleSystem::ExampleParticleSystem()
	{
		RegisterComponents<Transform, ExampleParticleSystemComponent>();
	}

	void ExampleParticleSystem::Init()
	{
		//ObjectPool::CreatePool(ecs_instance_, "TestParticle", 10);
		//ObjectPool::CreatePool(ecs_instance_, "TestParticle", 10);
	}

	// updates once per entity component per system per frame
	void ExampleParticleSystem::Update(const float& dt)
	{
		ExampleParticleSystemComponent& epsc = GetComponent<ExampleParticleSystemComponent>();
		if (epsc.timer_ > 0.02f)
		{
			ECS::Entity& e = ObjectPool::GetNewEntity(ecs_instance_, "TestParticle");

			// get particle entity and sets its attributes
			//ECS::Entity& e = ecs_instance_->GetEntity(id);

			// eg particle system code
			e.GetComponent<Transform>().position_ = GetComponent<Transform>().position_;
			float rand_dir_x = (static_cast<float>((rand() % 360 + 1) - 180)) / 180.0f;
			ExampleParticleComponent& epc = e.GetComponent<ExampleParticleComponent>();
			epc.direction_ = { rand_dir_x, 1.0f };
			epc.speed_ = static_cast<float>(10 + (rand() % 100 + 1));
			epsc.timer_ = 0.0f;
		}
		else
		{
			epsc.timer_ += dt;
		}
	}

	ExampleParticle::ExampleParticle()
	{
		RegisterComponents<Transform, ExampleParticleComponent>();
	}

	void ExampleParticle::Update(const float& dt)
	{
		ExampleParticleComponent& epc = GetComponent<ExampleParticleComponent>();
		GetComponent<Transform>().position_ += epc.direction_ * epc.speed_ * dt;
		GetComponent<Transform>().scale_.x += dt;
		GetComponent<Transform>().scale_.y += dt;
		if (epc.lifetime_ <= 0.0f)
		{
			epc.lifetime_ = 3.0f;
			// if life time up, flag as inactive to return it to object pool
			ToggleActiveFlag(false);
		}
		else
		{
			epc.lifetime_ -= dt;
		}
	}

	PopiahParticleSystem::PopiahParticleSystem()
	{
		RegisterComponents<Transform, PopiahPSFlag>();
	}

	void PopiahParticleSystem::Init()
	{
		//ObjectPool::CreatePool(ecs_instance_, "SpringRollParticle", 50);
	}

	// updates once per entity component per system per frame
	void PopiahParticleSystem::Update(const float& dt) 
	{
		UNREFERENCED_PARAMETER(dt);
		//if (timer_ < 0.0f)
		//{
		//	// create spring roll particle
		//	int id = ObjectPool::ActivateEntity(ecs_instance_, "SpringRollParticle");
		//	// set particle to this particle system position
		//	ecs_instance_->GetEntity(id).GetComponent<Transform>().position_ = GetComponent<Transform>().position_;
		//	// create 1 popiah per second
		//	timer_ = 1.0f;
		//}
		//else
		//{
		//	timer_ -= dt;
		//}
	}
}