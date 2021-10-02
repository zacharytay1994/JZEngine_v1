


#include "../Math/JZMath.h"
#include "../Physics/AABB.h"
#include <vector>

namespace JZEngine
{
    enum shapetype
    {
        circle = 0,
        aabb = 1,
        square = 2,
    };

    class PhysicsBody
    {
         Vec2f position;
         Vec2f linearVelocity;
         float rotation;
         float rotationalVelocity;
         Vec2f force;
    public:

        float Density;
        float Mass;
        float InvMass;
        float Restitution;
        float Area;

        bool IsStatic;

        float Radius;
        float Width;
        float Height;

        std::vector<Vec2f> vertices;
        std::vector<int> triangles;
        std::vector<Vec2f> transformedVertices;
        AABB aabb;

        bool transformUpdateRequired;
        bool aabbUpdateRequired;

        shapetype shapetype;

        Vec2f GetPosition()
        {
             { return this->position; }
        }

        Vec2f GetLinearVelocity()
        {
             { return this->linearVelocity; }
            
        }
        PhysicsBody() = default;
        PhysicsBody(Vec2f position, float density, float mass, float restitution, float area,
            bool isStatic, float radius, float width, float height, JZEngine::shapetype shapetype);
        ~PhysicsBody() {} 

        void CreateBoxTriangles();
        void CreateBoxVertices();
        void CreateCircleBody();
        void CreateBoxBody();
        void TransformVertices();
 
        /* 
        public FlatAABB GetAABB()
        {
            if (this->aabbUpdateRequired)
            {
                float minX = float.MaxValue;
                float minY = float.MaxValue;
                float maxX = float.MinValue;
                float maxY = float.MinValue;

                if (this->shapetype is shapetype.Box)
                {
                    Vec2f[] vertices = TransformedVertices();

                    for (int i = 0; i < vertices.Length; i++)
                    {
                        Vec2f v = vertices[i];

                        if (v.X < minX) { minX = v.X; }
                        if (v.X > maxX) { maxX = v.X; }
                        if (v.Y < minY) { minY = v.Y; }
                        if (v.Y > maxY) { maxY = v.Y; }
                    }
                }
                else if (this->shapetype is shapetype.Circle)
                {
                    minX = this->position.X - this->Radius;
                    minY = this->position.Y - this->Radius;
                    maxX = this->position.X + this->Radius;
                    maxY = this->position.Y + this->Radius;
                }
                else
                {
                    throw new Exception("Unknown shapetype.");
                }

                this->aabb = new FlatAABB(minX, minY, maxX, maxY);
            }

            this->aabbUpdateRequired = false;
            return this->aabb;
        }
    
        internal void Step(float time, Vec2f gravity, int iterations)
        {
            if (this->IsStatic)
            {
                return;
            }

            time /= (float)iterations;

            // force = mass * acc
            // acc = force / mass;

            //Vec2f acceleration = this->force / this->Mass;
            //this->linearVelocity += acceleration * time;


            this->linearVelocity += gravity * time;
            this->position += this->linearVelocity * time;

            this->rotation += this->rotationalVelocity * time;

            this->force = Vec2f.Zero;
            this->transformUpdateRequired = true;
            this->aabbUpdateRequired = true;
        }
        */
        void Move(Vec2f amount);
        void MoveTo(Vec2f position);
        void Rotate(float amount);
        void AddForce(Vec2f amount);


        
    };//physicsbody

}//JZEngine
