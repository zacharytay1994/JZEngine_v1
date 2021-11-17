/*	__FILE HEADER__
*	File:		RendererDebug.h
	Primary:	Zachary Tay
	Date:		01/07/21
	Brief:		Renders points, line, squares, and circles.
*/

#pragma once

#include <initializer_list>

#include "../GlobalSystems.h"
#include "../Math/JZMath.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "../Resource/ResourceManager.h"

namespace JZEngine
{
	struct RendererDebug
	{
		bool							initialized_		{ false };
		static constexpr unsigned int	MAX_POINTS			{ 1000 };
		static constexpr unsigned int	MAX_LINES			{ 1000 };
		static bool						draw_debug_;
		static bool						sprite_outline_;
		static float					point_size_;
		static std::vector<Vec2f>		sprite_lines_;
		static std::vector<Vec2f>		lines_;
		static std::vector<Vec2f>		points_;
		ResourceManager*				resource_manager_	{ nullptr };

		VertexArray		va_points_;
		VertexBuffer	vb_points_;

		VertexArray		va_lines_;
		VertexBuffer	vb_lines_;

		RendererDebug();

		void Initialize();
		void Update(ResourceManager* rm, float dt);

		static void DrawPoint(const Vec2f& p1);
		static void DrawLine(const Vec2f& p1, const Vec2f& p2);
		static void DrawLines(const std::initializer_list<Vec2f>& vertices, bool loop = false)
		{
			auto data = std::data(vertices);
			for (int i = 0; i < vertices.size() - 1; ++i)
			{
				DrawLine(data[i], data[i + 1]);
			}
			if (loop)
			{
				DrawLine(data[vertices.size() - 1], data[0]);
			}
		}
		static void DrawSpriteSquare(const Vec2f& centre, const Vec2f& dimensions);
		static void DrawSquare(const Vec2f& centre, const Vec2f& dimensions);
		static void DrawCircle(const Vec2f& centre, float radius, int density = 20);
		//static void DrawPolygon(const std::vector<Vec2f&> vertices);
	};
}