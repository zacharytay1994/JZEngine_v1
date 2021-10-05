#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/Collision.h"
#include "../GraphicRendering/RendererDebug.h"
#include "../Input/input.h"

#define PHYSICSDEBUG



namespace JZEngine
{
	std::vector<Transform*> transform_cont;

	
	PhysicsComponent::PhysicsComponent() {}
	PhysicsComponent::PhysicsComponent(const PhysicsComponent& s) { std::memcpy(this, &s, sizeof(s)); }
	PhysicsComponent::~PhysicsComponent() {}

	PhysicsSystem::PhysicsSystem()
	{
		RegisterComponents<PhysicsComponent,Transform>();
	}

	void PhysicsSystem::FrameBegin(const float& dt)
	{
		
	}

	//_____Updates Physic Components and calculates posnex for Collision & Response____//
	void PhysicsSystem::Update(const float& dt)
	{
		PhysicsComponent& current_pcomponent = GetComponent<PhysicsComponent>();
		Transform& current_transform = GetComponent<Transform>();


		//acceleration
		if (current_pcomponent.shapeid == shapetype::circle)
			current_pcomponent.velocity += current_pcomponent.acceleration * dt;

		current_pcomponent.posnex = current_transform.position_ + current_pcomponent.velocity * dt;

		
		if (current_pcomponent.shapeid == shapetype::circle)
		{
			current_pcomponent.m_circle.m_center = current_transform.position_;
			current_pcomponent.m_circle.m_radius = 0.5f * current_transform.size_.x;
		}
		if (current_pcomponent.shapeid == shapetype::square)
		{
			current_pcomponent.m_square = { current_transform.position_,current_transform.size_ };
			
		}
		//std::cout << current_pcomponent.shapeid << std::endl;
#ifdef PHYSICSDEBUG
		RendererDebug::DrawLine(current_transform.position_, current_transform.position_ + current_pcomponent.velocity * 0.2f);
#endif // 

		
		
		

		bool am_inside{ false };
		for (int i = 0; i < physics_cont.size(); ++i)
		{
			if (physics_cont[i] == &current_pcomponent)
			{
				am_inside = true;
				break;
			}
		}
		if (!am_inside)
		{
			physics_cont.push_back(&current_pcomponent);
			transform_cont.push_back(&current_transform);
		}


	}//__________________UPDATE_________________________//


	void PhysicsSystem::FrameEnd(const float& dt)
	{
		//Circle Circle
		for (int i = 0; i < physics_cont.size(); ++i)
		{
			PhysicsComponent& componentA = *physics_cont[i];
			for (int j = 0; j < physics_cont.size(); ++j)
			{
				PhysicsComponent& componentB = *physics_cont[j];

				if (&componentB == &componentA)
					continue;

				Vec2f interpta{}, interptb{}, normalatcollision{};
				float intertime{}, newspeed{};

				if (componentA.shapeid == circle && componentB.shapeid == circle)
				{
					if (true == Collision::DynamicCollision_CircleCircle(componentA.m_circle, componentA.velocity * dt, componentB.m_circle, componentB.velocity * dt, interpta, interptb, intertime))
					{

						Vec2f reflectedVecA, reflectedVecB, velA, velB;
						Vec2f normal = interpta - interptb;
						normal.Normalize();

						velA = componentA.velocity * dt;
						velB = componentB.velocity * dt;
						Vec2f posnexb;
						Collision::CollisionResponse_CircleCircle(normal, intertime, velA, componentA.mass, interpta, velB, componentB.mass, interptb,
							reflectedVecA, componentA.posnex, reflectedVecB, componentB.posnex);

						newspeed = reflectedVecA.Len() / dt;//A: new speed
						reflectedVecA.Normalize();//A: new speed direction
						componentA.velocity = reflectedVecA * newspeed;
						newspeed = reflectedVecB.Len() / dt;//B: new speed
						reflectedVecB.Normalize();
						componentB.velocity = reflectedVecB * newspeed;

#ifdef PHYSICSDEBUG
						Log::Info("Collision", "is circle-circle colliding!!!");
#endif
					}
				}
			}
		}
		for (int i = 0; i < static_cast<int>(physics_cont.size() - 1); i++)
		{
			PhysicsComponent& componentA = *physics_cont[i];
			Transform& componentA_transform = *transform_cont[i];
			for (int j = i + 1; j < physics_cont.size(); ++j)
			{
				PhysicsComponent& componentB = *physics_cont[j];
				Transform& componentB_transform = *transform_cont[j];


				Vec2f interpta{}, interptb{}, normalatcollision{};
				float intertime{}, newspeed{};

				if (componentA.shapeid == circle && componentB.shapeid == square)// Circle Square
				{
					float normal, depth;

					if (true == Collision::IntersectCirclePolygon(componentA.m_circle, componentB.m_square, normalatcollision, depth))
					{
						#ifdef PHYSICSDEBUG
												Log::Info("Collision", "Circle square sat");
						#endif
					}
					bool checkLineEdges = true;
					if (true == Collision::DynamicCollision_CircleSquare(componentA.m_circle, componentA.posnex, componentB.m_square, interpta, normalatcollision, intertime, checkLineEdges))
					{
#ifdef PHYSICSDEBUG
						Log::Info("Collision", "Circle square");
#endif
						Vec2f reflectedvel{};
						normalatcollision.Normalize();

						Collision::CollisionResponse_CircleLineSegment(interpta, normalatcollision, componentA.posnex, reflectedvel);
						componentA.velocity = reflectedvel * componentA.velocity.Len();
					}
						
				}
				if (componentA.shapeid == square && componentB.shapeid == circle)// square circle
				{
					float normal, depth;

					if (true == Collision::IntersectCirclePolygon(componentB.m_circle, componentA.m_square, normalatcollision, depth))
					{
#ifdef PHYSICSDEBUG
						Log::Info("Collision", "square circe sat");
#endif
					}

					bool checkLineEdges = true;
					if (true == Collision::DynamicCollision_CircleSquare(componentB.m_circle, componentB.posnex, componentA.m_square, interpta, normalatcollision, intertime, checkLineEdges))
					{
#ifdef PHYSICSDEBUG
						Log::Info("Collision", "square circle");
#endif
						Vec2f reflectedvel{};
						normalatcollision.Normalize();

						Collision::CollisionResponse_CircleLineSegment(interpta, normalatcollision, componentB.posnex, reflectedvel);
						componentB.velocity = reflectedvel * componentB.velocity.Len();
						
					}
				}
				if (componentA.shapeid == square && componentB.shapeid == square)// square square
				{
					if (&componentA == &componentB)
						continue;

					Vec2f normal;
					float depth=0.f;
					if (true==Collision::IntersectPolygons(componentA.m_square, componentB.m_square, normal,depth))
					{
#ifdef PHYSICSDEBUG
						Log::Info("Collision", "square square");
#endif
						componentA.posnex = componentA.m_square.midpoint - (normal * depth / 2.f);
						componentB.posnex = componentB.m_square.midpoint + (normal * depth / 2.f);
					}


				}
			}
		}
	
		if (InputHandler::IsKeyTriggered(KEY::KEY_P))
			pause = !pause;

		if (pause == false)
		{
			for (int i = 0; i < transform_cont.size(); ++i)
			{
				transform_cont[i]->position_ = physics_cont[i]->posnex;
				//transform_cont[i]->position_ += physics_cont[i]->velocity * dt;
			}
		}

		if (InputHandler::IsKeyTriggered(KEY::KEY_O))
			stepbystep = !stepbystep;
		if (stepbystep == true)
		{
			for (int i = 0; i < transform_cont.size(); ++i)
			{
				transform_cont[i]->position_ = physics_cont[i]->posnex;
				//transform_cont[i]->position_ += physics_cont[i]->velocity * dt;
			}
			stepbystep = !stepbystep;
		}

	}

}//JZEngine