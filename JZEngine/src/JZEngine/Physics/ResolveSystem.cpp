#include "PCH.h"
#include "ResolveSystem.h"

namespace JZEngine
{
	void Resolve::ResolvePhysicsCollision(PhysicsComponent & componentA, PhysicsComponent & componentB, const Vec2f & normal, const float& depth)
	{
	//Based on "Physics, Part 3: Collision Response" - Feb/Mar 97 By Chris Hecker
	//https://www.chrishecker.com/Rigid_Body_Dynamics#Physics_Articles
	//Linear Impulse

	Vec2f relativevelocity = componentB.velocity - componentA.velocity;

	if (relativevelocity.Dot(normal) > 0.f)
		return;

	float restitution = std::min(componentA.Restitution, componentB.Restitution);
	float j = -(1.f + restitution) * relativevelocity.Dot(normal);
	j /= componentA.InvMass + componentB.InvMass;
	Vec2f impulse = j * normal;
	componentA.velocity -= componentA.InvMass * impulse;
	componentB.velocity += componentB.InvMass * impulse;



	//This portion onwards is for friction
	relativevelocity = componentB.velocity - componentA.velocity;
	Vec2f tangent = relativevelocity - (relativevelocity.Dot(normal) * normal);
	if (tangent == Vec2f{ 0.0f, 0.0f })
		return;// rejection test if relative velocity is the same vector and -normal

	//tangent vector that is pointing more towards the relative velocity
	tangent.Normalize();
	float jt = -(relativevelocity.Dot(tangent));
	jt = jt / (componentA.InvMass + componentB.InvMass);

	//to not apply minute friction
	if (Math::IsEqual(jt, 0.0f))
		return;

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
}