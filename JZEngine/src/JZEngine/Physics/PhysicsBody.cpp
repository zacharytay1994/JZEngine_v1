#include "PCH.h"
#include "../Physics/PhysicsBody.h"
namespace JZEngine
{
    
    PhysicsBody::PhysicsBody(Vec2f position, float density, float mass, float restitution, float area,
        bool isStatic, float radius, float width, float height, JZEngine::ShapeType shapeType)
    {
        this->position = position;
        this->linearVelocity = { 0,0 };
        this->rotation = 0.f;
        this->rotationalVelocity = 0.f;

        this->force = { 0,0 };

        this->Density = density;
        this->Mass = mass;
        this->Restitution = restitution;
        this->Area = area;

        this->IsStatic = isStatic;
        this->Radius = radius;
        this->Width = width;
        this->Height = height;
        this->ShapeType = shapeType;

        if (!IsStatic)
        {
            this->InvMass = 1.f / this->Mass;
        }
        else
        {
            this->InvMass = 0.f;
        }

        if (this->ShapeType == JZEngine::Box)
        {
            CreateBoxVertices();
            CreateBoxTriangles();
            this->transformedVertices.reserve(4);
        }


        this->transformUpdateRequired = true;
        this->aabbUpdateRequired = true;
    }
    void PhysicsBody::CreateBoxTriangles()
    {
        triangles[0] = 0;
        triangles[1] = 1;
        triangles[2] = 2;
        triangles[3] = 0;
        triangles[4] = 2;
        triangles[5] = 3;

    }
    void PhysicsBody::CreateBoxVertices()
    {
        float left = -Width / 2.f;
        float right = left + Width;
        float bottom = -Height / 2.f;
        float top = bottom + Height;

        vertices[0] = Vec2f{ left, top };
        vertices[1] = Vec2f{ right, top };
        vertices[2] = Vec2f{ right, bottom };
        vertices[3] = Vec2f{ left, bottom };

    }

    void PhysicsBody::CreateCircleBody()
    {
        Area = Radius * Radius * Math::PI;
        std::clamp(Restitution, 0.f, 1.f);
        Mass = Area * Density;// mass = area * depth * density
    }

    void PhysicsBody::CreateBoxBody()
    {
        Area = Width * Height;
        std::clamp(Restitution, 0.f, 1.f);

        // mass = area * depth * density
        Mass = Area * Density;

    }

    void PhysicsBody::TransformVertices()
    {
        if (transformUpdateRequired)
        {
            transformedVertices = vertices;

            for (int i = 0; i < transformedVertices.size(); i++)
            {
                transformedVertices[i] -= - position;
                float rotatedX = transformedVertices[i].x * cosf(rotation) - transformedVertices[i].y * sin(rotation);
                float rotatedY = transformedVertices[i].x * sinf(rotation) + transformedVertices[i].y * cos(rotation);

                // translate back
                position.x = rotatedX + position.x;
                position.y = rotatedY + position.y;
            }
        }
        transformUpdateRequired = false;
    }

    void PhysicsBody::Move(Vec2f amount)
    {
        this->position += amount;
        this->transformUpdateRequired = true;
        this->aabbUpdateRequired = true;
    }

    void PhysicsBody::MoveTo(Vec2f position)
    {
        this->position = position;
        this->transformUpdateRequired = true;
        this->aabbUpdateRequired = true;
    }

    void PhysicsBody::Rotate(float amount)
    {
        this->rotation += amount;
        this->transformUpdateRequired = true;
        this->aabbUpdateRequired = true;
    }

    void PhysicsBody::AddForce(Vec2f amount)
    {
        this->force = amount;
    }


}
