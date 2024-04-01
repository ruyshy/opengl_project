#include <pch.h>
#include <OpenGL/Camera/Camera.h>

Camera::Camera(int window_width, int window_height)
{
	projection = glm::ortho(0.0f, static_cast<float>(window_width), static_cast<float>(window_height), 0.0f, -1.0f, 1.0f);
}

Camera::~Camera()
{

}

glm::mat4 Camera::Get_Projection()
{
	return projection;
}

void Camera::Update(std::function<bool(int)> key_input_function)
{
	if (key_input_function(GLFW_KEY_UP))
	{
		position.y += 2;
	}

}

void Camera::Update_Viewport(int new_width, int new_height)
{
	projection = glm::ortho(0.0f, static_cast<float>(new_width), static_cast<float>(new_height), 0.0f, -1.0f, 1.0f);
}
