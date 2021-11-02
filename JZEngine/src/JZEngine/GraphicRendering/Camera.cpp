#include <PCH.h>
#include "Camera.h"

#include "../JZGL/JZ_GL.h"
#include "../EngineGUI/MenuBar.h"

namespace JZEngine
{
	bool	Camera::fullscreen{ false };
	float	Camera::camera_zoom_{ 1.0f };
	Vec2f	Camera::camera_position_{ 0.0f, 0.0f };
	Vec2f	Camera::mouse_world_position_{ 0.0f, 0.0f };
	Mat3f	Camera::camera_transform_;

	void Camera::CalculateMouseWorldPosition(GLFWwindow* window)
	{
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        Vec2f screen_position_ = { static_cast<float>(x), static_cast<float>(y) };
        if (Camera::fullscreen)
        {
            Camera::mouse_world_position_.x = ((screen_position_.x / Settings::window_width) - 0.5f) * Settings::camera_width;
            Camera::mouse_world_position_.y = (-((screen_position_.y / Settings::window_height) - 0.5f)) * Settings::camera_height;
            Camera::mouse_world_position_.x += Camera::camera_position_.x;
            Camera::mouse_world_position_.y += Camera::camera_position_.y;
        }
        else
        {
            Camera::mouse_world_position_.x = ((screen_position_.x / Settings::window_width) - 0.5f) * Settings::camera_width * 1.5f;
            float percent = (MenuBar::height_ / Settings::window_height) + (0.375f * (1.0f - (MenuBar::height_ / Settings::window_height)));
            Camera::mouse_world_position_.y = (-(((screen_position_.y / Settings::window_height) - percent) / (0.375f * (1.0f - (MenuBar::height_ / Settings::window_height)))) * 0.5f) * Settings::camera_height;
            Camera::mouse_world_position_.x += Camera::camera_position_.x;
            Camera::mouse_world_position_.y += Camera::camera_position_.y;
        }
        //Log::Info("Main", "World Position: {}, {}", Camera::mouse_world_position_.x, Camera::mouse_world_position_.y);
	}
}