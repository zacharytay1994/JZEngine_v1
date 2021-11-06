#include "PCH.h"
#include "ResolveSystem.h"

namespace JZEngine
{
	void Resolve::ApplyImpulse(PhysicsComponent & componentA, PhysicsComponent & componentB, const Manifold& CollData)
	{
	//Based on "Physics, Part 3: Collision Response" - Feb/Mar 97 By Chris Hecker
	//https://www.chrishecker.com/Rigid_Body_Dynamics#Physics_Articles
	//Linear Impulse

	Vec2f relativevelocity = componentB.velocity - componentA.velocity;

	if (relativevelocity.Dot(CollData.normal) > 0.f)
		return;

	float restitution = std::min(componentA.Restitution, componentB.Restitution);
	float j = -(1.f + restitution) * relativevelocity.Dot(CollData.normal);
	j /= componentA.InvMass + componentB.InvMass;
	Vec2f impulse = j * CollData.normal;
	componentA.velocity -= componentA.InvMass * impulse;
	componentB.velocity += componentB.InvMass * impulse;



	//Friction
	relativevelocity = componentB.velocity - componentA.velocity; //recalculate relvel after impulse
	Vec2f tangent = relativevelocity - (relativevelocity.Dot(CollData.normal) * CollData.normal);
	if (tangent == Vec2f{ 0.0f, 0.0f })
		return;// rejection test if relative velocity is the same vector and -normal

	//tangent vector that is pointing more towards the relative velocity
	tangent.Normalize();
	float jt = -(relativevelocity.Dot(tangent));
	jt = jt / (componentA.InvMass + componentB.InvMass);

	//to not apply minute friction
	if (Math::IsEqual(jt, 0.0f))
		return;
	//Apply average friction of contact objs
	float mu = 0.5f * (componentA.StaticFriction + componentB.StaticFriction);
	Vec2f frictionimpulse;
	if (abs(jt) < (j * mu))
	{
		frictionimpulse = jt * tangent;
	}
	else
	{
		float dynamicfriction = 0.5f * (componentA.DynamicFriction + componentB.DynamicFriction);
		frictionimpulse = -j * tangent * dynamicfriction;
	}
	componentA.velocity -= componentA.InvMass * frictionimpulse;
	componentB.velocity += componentB.InvMass * frictionimpulse;

	}

	void Resolve::ResolveCollision(PhysicsComponent& componentA, PhysicsComponent& componentB, const Manifold& CollData)
	{
		const float minpen = 0.1f; // No need to resolve minute penetraction
		const float percent = 0.8f; // Penetration percentage to correct
		Vec2 correction = (std::max(CollData.depth - minpen, 0.0f) / (componentA.InvMass + componentB.InvMass)) * CollData.normal * percent;

		RigidBody::Move(componentA, -correction * componentA.InvMass);
		RigidBody::Move(componentB, correction * componentB.InvMass);
	}
}