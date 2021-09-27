#include "PCH.h"
#include "../ECS/ECS.h"
#include "../ECS/ECSConfig.h"

#define PHYSICSDEBUG
// #define GRAVITY
// #define SLOWDOWN


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

#ifdef GRAVITY
		if(current_component.shapeid != 1)
			current_component.acceleration.y = -0.098f; //gravity instead of 0
		
#endif
#ifdef SLOWDOWN
		current_component.velocity *= 0.98f;
#endif
		//apply accel
		if(current_component.shapeid==0)
			current_component.velocity += current_component.acceleration * dt;

		Transform& current_transform = GetComponent<Transform>();
	
		

		if (current_component.shapeid == 0)
		{
			current_component.m_circle.m_center = current_transform.position_;
			current_component.m_circle.m_radius = 0.5f*current_transform.size_.x ;

		}
		if (current_component.shapeid == 1)
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
						

						if (true == DynamicCollision_CircleCircle(current_component.m_circle, current_component.velocity*dt, physics_cont[i]->m_circle, physics_cont[i]->velocity*dt, interpta, interptb, intertime))
						{
							
							Vec2f reflectedVecA, reflectedVecB, velA, velB,posnex;
							Vec2f posNextB = transform_cont[i]->position_ + physics_cont[i]->velocity * dt;//not used yet, even though computed below

							Vec2f normal = interpta- interptb;
							normal.Normalize();

							velA = current_component.velocity * dt;
							velB = physics_cont[i]->velocity * dt;

							CollisionResponse_CircleCircle(normal, intertime, velA, current_component.mass, interpta, velB, physics_cont[i]->mass, interptb,
								reflectedVecA, posnex, reflectedVecB, posNextB);
							//posnexB not used
							newspeed = reflectedVecA.Len() / dt;//A: new speed
							reflectedVecA.Normalize();//A: new speed direction
							current_component.velocity = reflectedVecA * newspeed;

							newspeed = reflectedVecB.Len() / dt;//B: new speed
							reflectedVecB.Normalize();

							physics_cont[i]->velocity = reflectedVecB * newspeed;
							transform_cont[i]->position_ = posNextB;
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
							
							if (true == DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on right");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								current_component.velocity = reflectedvel * current_component.velocity.Len();
							}
						}

						//circle left of AABB
						else if (current_component.m_circle.m_center.x < physics_cont[i]->m_AABB.min.x)
						{
							 tmp_pt= { physics_cont[i]->m_AABB.min.x, physics_cont[i]->m_AABB.max.y };

							line= { physics_cont[i]->m_AABB.min, tmp_pt };

							if (true == DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on left");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								
								current_component.velocity = reflectedvel * current_component.velocity.Len();
							}

						}
						//circle above AABB
						if (current_component.m_circle.m_center.y > physics_cont[i]->m_AABB.max.y)
						{
							tmp_pt = { physics_cont[i]->m_AABB.min.x, physics_cont[i]->m_AABB.max.y };
							line={ physics_cont[i]->m_AABB.max, tmp_pt };
							if (true == DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime, checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle on top");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
								current_component.velocity = reflectedvel * current_component.velocity.Len();
								
							}
						}
						//circle below 
						else if (current_component.m_circle.m_center.y < physics_cont[i]->m_AABB.min.y)
						{
							tmp_pt = { physics_cont[i]->m_AABB.max.x, physics_cont[i]->m_AABB.min.y };
							line= { physics_cont[i]->m_AABB.min, tmp_pt };
							if (true == DynamicCollision_CircleLineSegment(current_component.m_circle, posnex, line, interpta, normalatcollision, intertime,checkLineEdges))
							{
#ifdef PHYSICSDEBUG
	Log::Info("Collision", "circle below");
#endif
								Vec2f reflectedvel{};
								normalatcollision.Normalize();
							
								CollisionResponse_CircleLineSegment(interpta, normalatcollision, posnex, reflectedvel);
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






	//Dynamic AABB collision
	bool PhysicsSystem::DynamicCollision_RectRect(const AABB& aabb1, const JZEngine::Vec2f& vel1,
		const AABB& aabb2, const JZEngine::Vec2f& vel2)
	{
		if ((aabb1.max.x < aabb2.min.x) || (aabb1.max.y < aabb2.min.y) || (aabb1.min.x > aabb2.max.x) || (aabb1.min.y > aabb2.max.y))
		{
			////Step 2: Initialize and calculate the new velocity of Vb
			float tFirst = 0.0f;
			float tLast = 0; // g_dt;
			Vec2f RelativeVb;
			RelativeVb = vel2 - vel1;
			if (!RelativeVb.x)
				if (aabb1.max.x < aabb2.min.x || aabb1.min.x > aabb2.max.x)
					return 0;
			if (!RelativeVb.y)
				if (aabb1.max.y < aabb2.min.y || aabb1.min.y > aabb2.max.y)
					return 0;
			if (RelativeVb.x)
			{
				if (RelativeVb.x < 0)
				{
					//case 1
					if (aabb1.min.x > aabb2.max.x)
					{
						return 0;
					}
					//case 4
					if (aabb1.max.x < aabb2.min.x)
					{
						tFirst = std::max((aabb1.max.x - aabb2.min.x) / RelativeVb.x, tFirst);
					}
					if (aabb1.min.x < aabb2.max.x)
					{
						tLast = std::max((aabb1.min.x - aabb2.max.x) / RelativeVb.x, tLast);
					}
				}
				else if (RelativeVb.x > 0)
				{
					//case 3
					if (aabb1.max.x < aabb2.min.x)
					{
						return 0;
					}
					//case 2
					if (aabb1.max.x > aabb2.min.x)
					{
						tFirst = std::max((aabb1.min.x - aabb2.max.x) / RelativeVb.x, tFirst);
					}
					if (aabb1.min.x > aabb2.max.x)
					{
						tLast = std::max((aabb1.max.x - aabb2.min.x) / RelativeVb.x, tLast);
					}
				}
				if (tFirst > tLast)
				{
					return 0;
				}
			}
			if (RelativeVb.y)
			{
				if (RelativeVb.y < 0)
				{
					//case 1
					if (aabb1.min.y > aabb2.max.y)
					{
						return 0;
					}
					//case 4
					if (aabb1.max.y < aabb2.min.y)
					{
						tFirst = std::max((aabb1.max.y - aabb2.min.y) / RelativeVb.y, tFirst);
					}
					if (aabb1.min.y < aabb2.max.y)
					{
						tLast = std::max((aabb1.min.y - aabb2.max.y) / RelativeVb.y, tLast);
					}
				}
				else if (RelativeVb.y > 0)
				{
					//case 3
					if (aabb1.max.y < aabb2.min.y)
					{
						return 0;
					}
					//case 2
					if (aabb1.min.y > aabb2.max.y)
					{
						tFirst = std::max((aabb1.min.y - aabb2.max.y) / RelativeVb.y, tFirst);
					}
					if (aabb1.max.y > aabb2.min.y)
					{
						tLast = std::max((aabb1.max.y - aabb2.min.y) / RelativeVb.y, tLast);
					}
				}
				//case 5
				if (tFirst > tLast)
				{
					return 0;
				}
			}
			return 0;
		}
		else
		{
			return 1; //rectangles intersect
		}
	}

	//Static AABB Collision
	bool PhysicsSystem::StaticCollision_PointRect(const Vec2f& point,
		const AABB& aabb2)
	{
		if (point.x < aabb2.max.x && point.x > aabb2.min.x && point.y < aabb2.max.y && point.y > aabb2.min.y)
			return 1;
		else return 0;
	}

	bool PhysicsSystem::CheckMovingCircleToLineEdge(bool withinBothLines,						//Flag stating that the circle is starting from between 2 imaginary line segments distant +/- Radius respectively - input
		const Circle& circle,													//Circle data - input
		const Vec2f& circleend,													//End circle position - input
		const LineSegment& lineSeg,												//Line segment - input
		Vec2f& interPt,														//Intersection point - output
		Vec2f& normalAtCollision,												//Normal vector at collision time - output
		float& interTime)
	{
		Vec2f V(circleend.x - circle.m_center.x, circleend.y - circle.m_center.y);
		Vec2f M(circleend.y - circle.m_center.y, -(circleend.x - circle.m_center.x));
		if (withinBothLines)
		{
			if ((lineSeg.m_pt0 - circle.m_center).Dot(lineSeg.m_pt1 - lineSeg.m_pt0) > 0.0f)//p0 side
			{
				float m = (lineSeg.m_pt0 - circle.m_center).Dot(V.GetNormalized());//BsP0V
				if (m > 0.0f)
				{
					float dist0 = (lineSeg.m_pt0 - circle.m_center).Dot(M.GetNormalized());
					if (abs(dist0) > circle.m_radius)
						return false;


					float s = sqrtf( (circle.m_radius * circle.m_radius) - (dist0 * dist0));
					interTime = (m - s) / V.Len();
					if (interTime <= 1.0f)
					{
						normalAtCollision = interPt - lineSeg.m_pt0;
						interPt = circle.m_center + V * interTime;
						return true;
					}
				}
			}
			else//(BsP1.P0P1 < 0) //P1 side //just return 1 for apply reflection in psuedo code 
			{
				float m = (lineSeg.m_pt1 - circle.m_center).Dot(V.GetNormalized());
				if (m <= 0)
					return false; //no collision
				//here means circle facing p1
				float dist1 = (lineSeg.m_pt1 - circle.m_center).Dot(M.GetNormalized());
				if (fabsf(dist1) > circle.m_radius)
					return false;
				float s = sqrtf((circle.m_radius * circle.m_radius) - (dist1 * dist1));
				interTime = (m - s) / V.Len();
				if (interTime <= 1.0f)
				{
					interPt = circle.m_center + V * interTime;
					normalAtCollision = interPt - lineSeg.m_pt1;
					return true;
				}

			}
		}
		else//not within both lines
		{
			bool p0side = false;
			float dist0 = (lineSeg.m_pt0 - circle.m_center).Dot(M.GetNormalized());
			float dist1 = (lineSeg.m_pt1 - circle.m_center).Dot(M.GetNormalized());

			float dist0_abs = abs(dist0);
			float dist1_abs = abs(dist1);

			if ((dist0_abs > circle.m_radius) && (dist1_abs > circle.m_radius))
				return false;

			else if ((dist0_abs <= circle.m_radius) && (dist1_abs <= circle.m_radius))
			{
				float m0 = (lineSeg.m_pt0 - circle.m_center).Dot(V.GetNormalized());
				float m1 = (lineSeg.m_pt1 - circle.m_center).Dot(V.GetNormalized());

				float m0_abs = abs(m0);
				float m1_abs = abs(m1);

				if (m0_abs < m1_abs) 
					{ p0side = true; }
				else 
					{ p0side = false; }

			}
			else if (dist0_abs <= circle.m_radius)
			{
				p0side = true;
			}
			else
			{
				p0side = false;
			}

			if (p0side)//circle close to p0
			{
				float m = (lineSeg.m_pt0 - circle.m_center).Dot(V.GetNormalized());
				if (m < 0.0f)
					return false;
				else
				{
					float s = sqrtf((circle.m_radius * circle.m_radius) - (dist0 * dist0));
					interTime = (m - s) / V.Len();
					if (interTime <= 1.0f)
					{
						interPt = circle.m_center + V * interTime;
						normalAtCollision = interPt - lineSeg.m_pt0;
						return true;
					}
				}
			}
			else//circle close to p1
			{
				float m = (lineSeg.m_pt1 - circle.m_center).Dot(V.GetNormalized());
				if (m < 0.0f)
					return false;
				else
				{
					float s = sqrtf((circle.m_radius * circle.m_radius) - (dist1 * dist1));
					interTime = (m - s) / V.Len();
					if (interTime <= 1.0f)
					{
						interPt = circle.m_center + V * interTime;
						normalAtCollision = interPt - lineSeg.m_pt1;
						return true;
					}
					else
						return false;
				}


			}


			return false;
		}
	}
	/******************************************************************************/
	/*!
	 * \brief			Function to check dynamic circle vs static line collision
	 * \param circle	The circle object which contains The middle pt of The circle n radius
	 * \param circleend	The end position of The circle, Be
	 * \param lineSeg	The object line segment which contains p0 p1 n The normal
	 * \param interPt	The intersection point, Bi
	 * \param normalAtCollision		The normal at collision
	 * \param interTime		The time of intersection, Ti
	 * \return 0 or 1		Returns 1 if collison detected, else 0
	 */
	 /******************************************************************************/
	bool PhysicsSystem::DynamicCollision_CircleLineSegment(const Circle& circle,			//Circle data - input
		const Vec2f& circleend,											//End circle position - input
		const LineSegment& lineSeg,												//Line segment - input
		Vec2f& interPt,												//Intersection point - output
		Vec2f& normalAtCollision,									//Normal vector at collision time - output
		float& interTime,
		bool checkLineEdges)//Intersection time ti - output												
	{
		
		
		// outward normal M to circle velocity
		Vec2f V(circleend.x - circle.m_center.x, circleend.y - circle.m_center.y);
		Vec2f M(circleend.y - circle.m_center.y, -(circleend.x - circle.m_center.x));
		float nbsnp0 = lineSeg.m_normal.Dot(circle.m_center) -
			lineSeg.m_normal.Dot(lineSeg.m_pt0);
		if (nbsnp0 <= -circle.m_radius)
		{
			Vec2f p0prime = lineSeg.m_pt0 - circle.m_radius * lineSeg.m_normal;
			Vec2f p1prime = lineSeg.m_pt1 - circle.m_radius * lineSeg.m_normal;

			if (M.Dot(p0prime - circle.m_center) * M.Dot(p1prime - circle.m_center) < 0)
			{
				interTime = (lineSeg.m_normal.Dot(lineSeg.m_pt0) - lineSeg.m_normal.Dot(circle.m_center) - circle.m_radius)
					/ lineSeg.m_normal.Dot(V);
				if (0 <= interTime && interTime <= 1)
				{
					interPt = circle.m_center + V * interTime;
					normalAtCollision = -lineSeg.m_normal;
					
					return true;
				}
				else
					return false;
			}
			else
			{
				checkLineEdges = false;
				bool retva=CheckMovingCircleToLineEdge(checkLineEdges, circle, circleend, lineSeg, interPt, normalAtCollision, interTime);
				//CollisionResponse_CircleLineSegment(interPt, normalatcollision, circleend, reflectedvel);
				return retva;
			}
		}
		else if (nbsnp0 >= circle.m_radius)
		{
			Vec2f p0prime = lineSeg.m_pt0 + circle.m_radius * lineSeg.m_normal;
			Vec2f p1prime = lineSeg.m_pt1 + circle.m_radius * lineSeg.m_normal;

			if ((M.Dot(p0prime - circle.m_center) * M.Dot(p1prime - circle.m_center)) < 0)
			{
				interTime = (lineSeg.m_normal.Dot(lineSeg.m_pt0) - lineSeg.m_normal.Dot(circle.m_center) + circle.m_radius)
					/ lineSeg.m_normal.Dot(V);
				if (0 <= interTime && interTime <= 1)
				{
					interPt = circle.m_center + V * interTime;
					normalAtCollision = lineSeg.m_normal;
					
					return true;
					
				}
				else
					return false;
			}
			else
			{
				checkLineEdges = false;
				bool retva = CheckMovingCircleToLineEdge(checkLineEdges, circle, circleend, lineSeg, interPt, normalAtCollision, interTime);
				//return ();
				return retva;
			}
		}
		else
		{
			checkLineEdges = true;
			bool retva = CheckMovingCircleToLineEdge(checkLineEdges, circle, circleend, lineSeg, interPt, normalAtCollision, interTime);
			return retva;
		
		}
	}

	/******************************************************************************/
	/**
	 * @brief Collision checker for 2 dynamic circles
	 *
	 * @param circleA First circle object
	 * @param velA 		Velocity if first circle
	 * @param circleB Second circle object
	 * @param velB 		Velocity of second circle
	 * @param interPtA Intersection point of first circle
	 * @param interPtB Intersection point of second circle
	 * @param interTime Intersection time
	 * @return bool true if collided
	 */
	 /******************************************************************************/
	bool PhysicsSystem::DynamicCollision_CircleCircle(const Circle& circleA,
		const Vec2f& velA,
		const Circle& circleB,
		const Vec2f& velB,
		Vec2f& interPtA,
		Vec2f& interPtB,
		float& interTime)
	{
		Vec2f RV, nRV;
		RV = velA - velB;
		float RVlength = RV.Len();
		nRV = RV.GetNormalized();

		float m = nRV.Dot(circleB.m_center - circleA.m_center);
		//first rejection test
		if (m < 0)
			return 0;
		float n2 = (circleB.m_center - circleA.m_center).LenSq() - (m * m);
		float r = circleA.m_radius + circleB.m_radius;
		//second rejection test
		if (n2 > r * r)
			return 0;

		float s2 = r * r - n2;
		interTime = (m - sqrt(s2)) / RVlength;
		if (interTime > 0.0f && interTime < 1.0f)
		{
			interPtA = circleA.m_center + velA * interTime;
			interPtB = circleB.m_center + velB * interTime;
			return 1;
		}
		else
			return 0;
	}

	/******************************************************************************/
	/*!
	 * \brief			The function which handles The response to collision
	 * \param ptInter	The point of intersection,Bi
	 * \param normal	The normal at intersection
	 * \param ptEnd		The end of The circle applying reflection
	 * \param reflected	The reflection vector(normalized)
	 */
	 /******************************************************************************/
	void PhysicsSystem::CollisionResponse_CircleLineSegment(const Vec2f& ptInter,
		const Vec2f& normal,
		Vec2f& ptEnd,
		Vec2f& reflected)
	{
	
		reflected = (ptEnd - ptInter) - (2.0f * normal.Dot(ptEnd - ptInter) * normal);
		ptEnd = ptInter + reflected;
		reflected.Normalize();
	}

	/**
	 * \brief This function handles the collision response for circle with circle objects
	 * \param normal
	 * \param interTime
	 * \param velA
	 * \param massA
	 * \param interPtA
	 * \param velB
	 * \param massB
	 * \param interPtB
	 * \param reflectedVectorA
	 * \param ptEndA
	 * \param reflectedVectorB
	 * \param ptEndB
	 */
	void PhysicsSystem::CollisionResponse_CircleCircle(Vec2f& normal,
		const float interTime,
		const Vec2f& velA,
		const float& massA,
		Vec2f& interPtA,
		const Vec2f& velB,
		const float& massB,
		Vec2f& interPtB,
		Vec2f& reflectedVectorA,
		Vec2f& ptEndA,
		Vec2f& reflectedVectorB,
		Vec2f& ptEndB)
	{
		Vec2f nnormal;
		Vec2f nreflectedVectorA, nreflectedVectorB;
		//Vector2DNormalize(nnormal, normal);
		float aA = velA.Dot(normal);
		float aB = velB.Dot(normal);
		reflectedVectorA = velA -  ((2 * (aA - aB)) / (massA + massB)) * massB * normal;
		reflectedVectorB = velB + ((2 * (aA - aB)) / (massA + massB)) * massA * normal;
		nreflectedVectorA = reflectedVectorA.GetNormalized();
		nreflectedVectorB = reflectedVectorB.GetNormalized();

		ptEndA = interPtA + nreflectedVectorA * (1.0f - interTime);
		ptEndB = interPtB + nreflectedVectorB * (1.0f - interTime);
	}






}//JZEngine