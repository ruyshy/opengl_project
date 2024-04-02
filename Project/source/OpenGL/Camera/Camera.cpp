#include <pch.h>
#include <OpenGL/Camera/Camera.h>

Camera::Camera(shared_ptr<int> window_width, shared_ptr<int> window_height)
{
	mpWidth = window_width;
	mpHeight = window_height;

	mProjection = glm::ortho(0.0f, static_cast<float>(*mpWidth), static_cast<float>(*mpHeight), 0.0f, -1.0f, 1.0f);
	mPosition = vec2(0, 0);
}

Camera::~Camera()
{

}

glm::mat4 Camera::Get_Projection() { return mProjection; }

void Camera::SetPosition(vec2 position) { mPosition = position; }

void Camera::Key_Update(std::function<bool(int)> key_input_function, double delta_time)
{
	if (key_input_function(GLFW_KEY_UP))
		mPosition.y -= 10 * delta_time;
	else if (key_input_function(GLFW_KEY_DOWN))
		mPosition.y += 10 * delta_time;
	else if (key_input_function(GLFW_KEY_LEFT))
		mPosition.x -= 10 * delta_time;
	else if (key_input_function(GLFW_KEY_RIGHT))
		mPosition.x += 10 * delta_time;

}

void Camera::Update()
{
	mProjection = glm::ortho(mPosition.x, mPosition.x + static_cast<float>(*mpWidth),
		mPosition.y + static_cast<float>(*mpHeight), mPosition.y, -1.0f, 1.0f);
}

