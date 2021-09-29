#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"
#include "../Physics/Collision.h"
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
		j = 0;
	}

	// updates once per entity component per system per frame
	void PhysicsSystem::Update(const float& dt)
	{
		PhysicsComponent& current_component = GetComponent<PhysicsComponent>();


		if (current_component.shapeid == shapetype::circle)
			current_component.velocity += current_component.acceleration * dt;

		Transform& current_transform = GetComponent<Transform>();
		
		if (current_component.shapeid == shapetype::circle)
		{
			current_component.m_circle.m_center = current_transform.position_;
			current_component.m_circle.m_radius = 0.5f * current_transform.size_.x;

		}
		if (current_component.shapeid == shapetype::aabb)
		{
			AABB tmp{ current_transform.position_,current_transform.size_ };
			current_component.m_AABB = tmp;
		}
		

		Vec2f posnex{};
		posnex = current_transform.position_ + current_component.velocity * dt;
		bool am_inside{ false };
		for (int i = 0; i < physics_cont.size(); ++i)
		{
			// to not check with itself
			if (physics_cont[i] != &current_component)
			{
				Vec2f interpta{}, interptb{}, normalatcollision{}, tmp_pt{};
				float intertime{}, newspeed{};
				LineSegment line{};

				
				switch (current_component.shapeid)
				{
				case 0:
					
					switch (physics_cont[i]->shapeid)
					{
					case 0://  dynamic circle dynamic circle 
						

						if (true == Collision::DynamicCollision_CircleCircle(current_component.m_circle, current_component.velocity*dt, physics_cont[i]->m_circle, physics_cont[i]->velocity*dt, interpta, interptb, intertime))
						{
							
							Vec2f reflectedVecA, reflectedVecB, velA, velB;
							Vec2f posNextB;// = transform_cont[i]->position_ + physics_cont[i]->velocity * dt;//cannot use(wont work)

							Vec2f normal = interpta- interptb;
							normal.Normalize();

							velA = current_component.velocity * dt;
							velB = physics_cont[i]->velocity * dt;

							Collision::CollisionResponse_CircleCircle(normal, intertime, velA, current_component.mass, interpta, velB, physics_cont[i]->mass, interptb,
								reflectedVecA, posnex, reflectedVecB, posNextB);
							//posnexB not used
							newspeed = reflectedVecA.Len() / dt;//A: new speed
							reflectedVecA.Normalize();//A: new speed direction
							current_component.velocity = reflectedVecA * newspeed;

							newspeed = reflectedVecB.Len() / dt;//B: new speed
							reflectedVecB.Normalize();

							physics_cont[i]->velocity = reflectedVecB * newspeed;
							//transform_cont[i]->position_ = posNextB;
							//current_transform.position_ = posnex;

#ifdef PHYSICSDEBUG
	Log::Info("Collision", "is circle-circle colliding!!!");
#endif
						}

						break;
					case 1:// dynamic circle vs static AABB
						bool checkLineEdges = false;
						//circle right of AABB
						if (current_component.m_circle.m_center.x > physics_cont[i]->m_AABB.max.x)
						{
							tmp_pt = { physics_cont[i]->m_AABB.max.x, physics_cont[i]->m_AABB.min.y };
							line= { physics_cont[i]->m_AABB.max, tmp_pt };
							
							if (true == Collision::DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on right");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								Collision::CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								current_component.velocity = reflectedvel * current_component.velocity.Len();
							}
						}

						//circle left of AABB
						else if (current_component.m_circle.m_center.x < physics_cont[i]->m_AABB.min.x)
						{
							 tmp_pt= { physics_cont[i]->m_AABB.min.x, physics_cont[i]->m_AABB.max.y };

							line= { physics_cont[i]->m_AABB.min, tmp_pt };

							if (true == Collision::DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on left");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								Collision::CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								
								current_component.velocity = reflectedvel * current_component.velocity.Len();
							}

						}
						//circle above AABB
						if (current_component.m_circle.m_center.y > physics_cont[i]->m_AABB.max.y)
						{
							tmp_pt = { physics_cont[i]->m_AABB.min.x, physics_cont[i]->m_AABB.max.y };
							line={ physics_cont[i]->m_AABB.max, tmp_pt };
							if (true == Collision::DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on top");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								Collision::CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								current_component.velocity = reflectedvel * current_component.velocity.Len();
								
							}
						}
						//circle below 
						else if (current_component.m_circle.m_center.y < physics_cont[i]->m_AABB.min.y)
						{
							tmp_pt = { physics_cont[i]->m_AABB.max.x, physics_cont[i]->m_AABB.min.y };
							line= { physics_cont[i]->m_AABB.min, tmp_pt };
							if (true == Collision::DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime,checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle below");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								Collision::CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								current_component.velocity = reflectedvel * current_component.velocity.Len();
							}
						}
						
						//current_transform.position_ = posnex;
						
						break;
					}
					break;
#if 0
				case 1:
					 posnex =transform_cont[i]->position_ + physics_cont[i]->velocity * dt;
					switch (physics_cont[i]->shapeid)
					{
					case 0:
						bool checkLineEdges = false;
						//circle right of AABB
						if (physics_cont[i]->m_circle.m_center.x > current_component.m_AABB.max.x)
						{
							tmp_pt = { current_component.m_AABB.max.x, current_component.m_AABB.min.y };
							line = { current_component.m_AABB.max, tmp_pt };

							if (true == DynamicCollision_CircleLineSegment(physics_cont[i]->m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on right");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();

								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								physics_cont[i]->velocity = reflectedvel * physics_cont[i]->velocity.Len();
							}
						}

						//circle left of AABB
						else if (physics_cont[i]->m_circle.m_center.x < current_component.m_AABB.min.x)
						{
							tmp_pt = { current_component.m_AABB.min.x, current_component.m_AABB.max.y };

							line = { current_component.m_AABB.min, tmp_pt };

							if (true == DynamicCollision_CircleLineSegment(physics_cont[i]->m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on left");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();

								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);

								physics_cont[i]->velocity = reflectedvel * physics_cont[i]->velocity.Len();
							}

						}
						//circle above AABB
						if (physics_cont[i]->m_circle.m_center.y > current_component.m_AABB.max.y)
						{
							tmp_pt = { current_component.m_AABB.min.x, current_component.m_AABB.max.y };
							line = { current_component.m_AABB.max, tmp_pt };
							if (true == DynamicCollision_CircleLineSegment(physics_cont[i]->m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on top");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();

								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								physics_cont[i]->velocity = reflectedvel * physics_cont[i]->velocity.Len();

							}
						}
						//circle below 
						else if (physics_cont[i]->m_circle.m_center.y < current_component.m_AABB.min.y)
						{
							tmp_pt = { current_component.m_AABB.max.x, current_component.m_AABB.min.y };
							line = { current_component.m_AABB.min, tmp_pt };
							if (true == DynamicCollision_CircleLineSegment(physics_cont[i]->m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle below");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();

								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								physics_cont[i]->velocity = reflectedvel * physics_cont[i]->velocity.Len();
							}
						}
						current_transform.position_ = posnex;

						break;
					}
#endif

				}
			}
			else
			{
				am_inside = true;
			}
		}
		if (!am_inside)
		{
			physics_cont.push_back(&current_component);
			transform_cont.push_back(&current_transform);
		}
		++j;
		current_transform.position_ = posnex;



	}//__________________UPDATE_________________________//










}//JZEngine