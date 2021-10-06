#include <PCH.h>
#include "RendererDebug.h"

namespace JZEngine
{
	std::vector<Vec2f>	RendererDebug::sprite_lines_;
	std::vector<Vec2f>	RendererDebug::lines_;
	std::vector<Vec2f>	RendererDebug::points_;
	bool				RendererDebug::draw_debug_{ false };
	bool				RendererDebug::sprite_outline_{ false };
	float				RendererDebug::point_size_{ 5.0f };

	RendererDebug::RendererDebug()
		:
		vb_points_(static_cast<unsigned int>(MAX_POINTS * sizeof(Vec2f))),
		vb_lines_(static_cast<unsigned int>(MAX_LINES * 2 * sizeof(Vec2f)))
	{
		VertexBufferLayout layout_points;
		layout_points.Push<float>(2);
		va_points_.AddBuffer(vb_points_, layout_points);
		va_points_.Unbind();
		vb_points_.Unbind();

		VertexBufferLayout layout_lines;
		layout_lines.Push<float>(2);
		va_lines_.AddBuffer(vb_lines_, layout_lines);
		va_lines_.Unbind();
		vb_lines_.Unbind();
	}

	void RendererDebug::Init()
	{
		resource_manager_ = GetSystem<ResourceManager>();
		initialized_ = true;
	}

	void RendererDebug::Update(float dt)
	{
		if (initialized_)
		{
			if (sprite_outline_)
			{
				// draw sprite lines
				va_lines_.Bind();
				resource_manager_->debug_shaders_[1].shader_program_.Bind();
				resource_manager_->debug_shaders_[1].shader_program_.SetUniform("uColor", { 1.0f,1.0f,1.0f });
				resource_manager_->debug_shaders_[1].shader_program_.SetUniform("projection", Math::GetProjectionTransformNonTransposed().Transpose());
				for (int start = 0; start < sprite_lines_.size(); start += MAX_LINES)
				{
					int size = std::min(MAX_LINES, static_cast<unsigned int>(sprite_lines_.size() - start));
					vb_lines_.SetData(sprite_lines_.data() + start, size * sizeof(Vec2f));
					glDrawArrays(GL_LINES, 0, size);
				}
				resource_manager_->debug_shaders_[1].shader_program_.Unbind();
				va_lines_.Unbind();
				sprite_lines_.clear();
			}

			if (draw_debug_)
			{
				// draw lines
				va_lines_.Bind();
				resource_manager_->debug_shaders_[1].shader_program_.Bind();
				resource_manager_->debug_shaders_[1].shader_program_.SetUniform("uColor", { 1.0f,1.0f,1.0f });
				resource_manager_->debug_shaders_[1].shader_program_.SetUniform("projection", Math::GetProjectionTransformNonTransposed().Transpose());
				for (int start = 0; start < lines_.size(); start += MAX_LINES)
				{
					int size = std::min(MAX_LINES, static_cast<unsigned int>(lines_.size() - start));
					vb_lines_.SetData(lines_.data() + start, size * sizeof(Vec2f));
					glDrawArrays(GL_LINES, 0, size);
				}
				resource_manager_->debug_shaders_[1].shader_program_.Unbind();
				va_lines_.Unbind();
				lines_.clear();

				// draw points
				glPointSize(point_size_);
				va_points_.Bind();
				resource_manager_->debug_shaders_[0].shader_program_.Bind();
				resource_manager_->debug_shaders_[1].shader_program_.SetUniform("uColor", { 1.0f,1.0f,1.0f });
				resource_manager_->debug_shaders_[0].shader_program_.SetUniform("projection", Math::GetProjectionTransformNonTransposed().Transpose());
				for (int start = 0; start < points_.size(); start += MAX_POINTS)
				{
					int size = std::min(MAX_POINTS, static_cast<unsigned int>(points_.size() - start));
					vb_points_.SetData(points_.data() + start, size * sizeof(Vec2f));
					glDrawArrays(GL_POINTS, 0, size);
				}
				resource_manager_->debug_shaders_[0].shader_program_.Unbind();
				va_points_.Unbind();
				points_.clear();
			}
		}
	}

	void RendererDebug::DrawPoint(const Vec2f& p1)
	{
		points_.emplace_back(p1);
	}

	void RendererDebug::DrawLine(const Vec2f& p1, const Vec2f& p2)
	{
		lines_.emplace_back(p1);
		lines_.emplace_back(p2);
	}

	void RendererDebug::DrawSpriteSquare(const Vec2f& centre, const Vec2f& dimensions)
	{
		float half_width = dimensions.x / 2.0f;
		float half_height = dimensions.y / 2.0f;

		// calculate corners of square
		Vec2f p0{ centre.x - half_width, centre.y + half_height };
		Vec2f p1{ centre.x - half_width, centre.y - half_height };
		Vec2f p2{ centre.x + half_width, centre.y - half_height };
		Vec2f p3{ centre.x + half_width, centre.y + half_height };

		// render edges as lines
		sprite_lines_.emplace_back(p0); sprite_lines_.emplace_back(p1);
		sprite_lines_.emplace_back(p1); sprite_lines_.emplace_back(p2);
		sprite_lines_.emplace_back(p2); sprite_lines_.emplace_back(p3);
		sprite_lines_.emplace_back(p3); sprite_lines_.emplace_back(p0);
	}

	void RendererDebug::DrawSquare(const Vec2f& centre, const Vec2f& dimensions)
	{
		float half_width = dimensions.x / 2.0f;
		float half_height = dimensions.y / 2.0f;

		// calculate corners of square
		Vec2f p0{ centre.x - half_width, centre.y + half_height };
		Vec2f p1{ centre.x - half_width, centre.y - half_height };
		Vec2f p2{ centre.x + half_width, centre.y - half_height };
		Vec2f p3{ centre.x + half_width, centre.y + half_height };

		// render edges as lines
		DrawLine(p0, p1);
		DrawLine(p1, p2);
		DrawLine(p2, p3);
		DrawLine(p3, p0);
	}

	void RendererDebug::DrawCircle(const Vec2f& centre, float radius, int density)
	{
		Vec2f radius_vec{ radius, 0.0f };
		float iteration = Math::PIx2 / density;
		Vec2f p1;
		Vec2f p2;
		for (int i = 0; i < density; ++i)
		{
			p1 = centre + Math::GetRotatedVector(radius_vec, iteration * i);
			p2 = centre + Math::GetRotatedVector(radius_vec, iteration * (i+1));
			DrawLine(p1, p2);
		}
	}


}