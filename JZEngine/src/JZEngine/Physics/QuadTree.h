#pragma once
#include <memory>
#include "../Math/JZMath.h"
#include "../Physics/PhysicsShapes.h"
#include "CollisionComponent.h"
#include "Rect.h"
#include "PhyicsDebug.h"


namespace JZEngine
{
	template <typename T>
	class Quadtree 
	{
	public:
		template <typename T>
		class QtNode 
		{
		public:
			QtNode(const Rect& boundary)
				:
				boundary(boundary)
			{}
			// sets a node state divided to true, and initializes its inner nodes
			void Subdivide() 
			{
				float halfHeight = boundary.height / 4.0f;
				float halfWidth = boundary.width / 4.0f;
				northWest = std::make_unique<QtNode<T>>(Rect(Vec2f(boundary.rectCenter.x - halfWidth, boundary.rectCenter.y + halfHeight), halfWidth * 2.0f, halfHeight * 2.0f));
				northEast = std::make_unique<QtNode<T>>(Rect(Vec2f(boundary.rectCenter.x + halfWidth, boundary.rectCenter.y + halfHeight), halfWidth * 2.0f, halfHeight * 2.0f));
				southWest = std::make_unique<QtNode<T>>(Rect(Vec2f(boundary.rectCenter.x - halfWidth, boundary.rectCenter.y - halfHeight), halfWidth * 2.0f, halfHeight * 2.0f));
				southEast = std::make_unique<QtNode<T>>(Rect(Vec2f(boundary.rectCenter.x + halfWidth, boundary.rectCenter.y - halfHeight), halfWidth * 2.0f, halfHeight * 2.0f));
				divided = true;
			}

			// inserts an elements into a node,
			// if node is not full and not divided, add it to its element container,
			// if node is full and not divided, subdivide the node, and recursively move all elements into inner nodes
			// if node is full and divided, recursively insert into inner nodes
			void InsertElement(T* element) 
			{
				if (nodeArray.size() < capacity && !divided) 
				{
					nodeArray.push_back(element);
				}
				else 
				{
					if (!divided) 
					{
						nodeArray.push_back(element);
						Subdivide();
						// move points from parent node to subdivided child nodes
						for (T* e : nodeArray) 
						{
							// check to see which quadrant element lies in and insert element into quadrant
							switch (IsIn(e)) 
							{
							case 0:
								northWest->InsertElement(std::move(e));
								break;
							case 1:
								northEast->InsertElement(std::move(e));
								break;
							case 2:
								southWest->InsertElement(std::move(e));
								break;
							case 3:
								southEast->InsertElement(std::move(e));
								break;
							}
						}
					}
					else 
					{
						// check to see which quadrant element lies in and insert element into quadrant
						switch (IsIn(element)) 
						{
						case 0:
							northWest->InsertElement(element);
							break;
						case 1:
							northEast->InsertElement(element);
							break;
						case 2:
							southWest->InsertElement(element);
							break;
						case 3:
							southEast->InsertElement(element);
							break;
						}
					}

				}
			}
			// check if the elements position in world space, fall within a node's boundary
			int IsIn(T* e) 
			{
				float xPos = e->pos.x;
				float yPos = e->pos.y;
				// top left quadrant
				if (xPos < boundary.rectCenter.x && yPos > boundary.rectCenter.y)
					return 0;
				// top right quadrant
				else if (xPos > boundary.rectCenter.x && yPos > boundary.rectCenter.y) 
					return 1;
				// bottom left quadrant											 
				else if (xPos < boundary.rectCenter.x && yPos < boundary.rectCenter.y)
					return 2;
				// bottom right quadrant										  
				else if (xPos > boundary.rectCenter.x && yPos < boundary.rectCenter.y) 
					return 3;
				else 
					return -1;
				
			}
			// query if range overlaps with node boundary,
			// if node does overlap and is divided, recursively query inner nodes,
			// if node does overlap and is not divided, check with all elements held by that node to see if elements fall within range
			void QueryQt(Rect& range, int& hits, const float& yHeight, const float& sizeRadius) 
			{
				if (range.IsOverlapRect(boundary)) 
				{
					// if not divided return points within boundary
					if (!divided) 
					{
						for (T* e : nodeArray) 
						{
							if (range.IsOverlap(e->pos) && (abs(e->pos.y - yHeight) < sizeRadius)) 
							{

							}

						}
					}
					// if divided query inner nodes
					else {
						northWest->QueryQt(range, hits, yHeight, sizeRadius);
						northEast->QueryQt(range, hits, yHeight, sizeRadius);
						southWest->QueryQt(range, hits, yHeight, sizeRadius);
						southEast->QueryQt(range, hits, yHeight, sizeRadius);
					}
				}
			}
			// normal query returning elements within range
			void GetElements(Rect& range, std::vector<T*>& passDownContainer, T* self) 
			{
				if (range.IsOverlapRect(boundary)) 
				{
					// if not divided return points within boundary
					if (!divided) 
					{
						for (T* e : nodeArray) 
						{
							if (e != self) 
							{
								passDownContainer.push_back(e);
							}
						}
					}
					// if divided query inner nodes
					else 
					{
						northWest->GetElements(range, passDownContainer, self);
						northEast->GetElements(range, passDownContainer, self);
						southWest->GetElements(range, passDownContainer, self);
						southEast->GetElements(range, passDownContainer, self);
					}
				}
			}

			void DrawNode() 
			{
				if (!divided)
				{
					{
						// rectangle corner positions of node, mainly for debugging drawing purposes 
						Vec2f topLeft = { boundary.rectCenter.x - boundary.width / 2.0f, (boundary.rectCenter.y + boundary.height / 2.0f) };
						Vec2f topRight = { topLeft.x + boundary.width, topLeft.y };
						Vec2f bottomLeft = { topLeft.x, topLeft.y - boundary.height };
						Vec2f bottomRight = { bottomLeft.x + boundary.width ,bottomLeft.y };
							
						PhysicsDebug::DebugDrawLine(topLeft, topRight);
						PhysicsDebug::DebugDrawLine(topRight, bottomRight);
						PhysicsDebug::DebugDrawLine(bottomRight, bottomLeft);
						PhysicsDebug::DebugDrawLine(bottomLeft, topLeft);
					}
					
				}
				// if divided
				else
				{
					northWest->DrawNode();
					northEast->DrawNode();
					southWest->DrawNode();
					southEast->DrawNode();
				}
			}

		public:
			// rectangle aabb of node
			Rect boundary;
		private:

			// maximum number of elements per node before having to divide
			float capacity = 4;
			// boolean state whether node has been divided or not
			bool divided = false;
			// array that contains elements belonging to the node, its not actually and array of nodes, more of an array of elements
			// poor naming convention
			std::vector<T*> nodeArray;
			// inner subdivided nodes held
			std::unique_ptr<QtNode<T>> northWest;
			std::unique_ptr<QtNode<T>> northEast;
			std::unique_ptr<QtNode<T>> southWest;
			std::unique_ptr<QtNode<T>> southEast;

		};
	public:
		Quadtree(float sizex, float sizey)
			:
			rootNode(std::make_unique<QtNode<T>>(Rect(Vec2f(0.0f, 0.0f), sizex, sizey))),
			size{ sizex, sizey }
		{}

		// inserts element into root node, i.e. start the recursive ball rolling of inserting into inner nodes
		void InsertElement(T* element) 
		{
			// ensure element lies within world boundary
			if (element->pos.x > (rootNode->boundary.rectCenter.x - rootNode->boundary.width / 2.0f) && element->pos.x < (rootNode->boundary.rectCenter.x + rootNode->boundary.width / 2.0f) &&
				element->pos.y >(rootNode->boundary.rectCenter.y - rootNode->boundary.height / 2.0f) && element->pos.y < (rootNode->boundary.rectCenter.y + rootNode->boundary.height / 2.0f)) 
			{
				rootNode->InsertElement(element);
			}
		}
		// resets the node by discarding the object being pointed to and replacing it with a new one
		// this is done per frame to refresh the quadtree for updated referencing
		void Reset() 
		{
			rootNode.reset(new QtNode<T>(Rect(Vec2f(0.0f, 0.0f), size.x, size.y)));
			//ss << "root reset" << std::endl;
		}
		// queries the quadtree recursively through the nodes, and does stuff to elements that falls within range
		void QueryQt(Rect& queryRange, int& hits, const float& yHeight, const float& sizeRadius) 
		{
			rootNode->QueryQt(queryRange, hits, yHeight, sizeRadius);
		}


		std::vector<T*> GetElements(Rect& queryRange, T* self) 
		{
			std::vector<T*> container;
			rootNode->GetElements(queryRange, container, self);
			return container;
		}

		void DrawQt()
		{
			rootNode->DrawNode();
		}

	private:
		std::unique_ptr<QtNode<T>> rootNode;
		// size of root boundary, i.e. the span of the quadtree in world/model size, centered on world position (0,0,0)
		Vec2f size;

	};
}
