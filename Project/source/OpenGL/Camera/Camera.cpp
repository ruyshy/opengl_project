#include <pch.h>
#include <OpenGL/Camera/Camera.h>

Camera::Camera(int window_width, int window_height)
{
	mProjection = glm::ortho(0.0f, static_cast<float>(window_width), static_cast<float>(window_height), 0.0f, -1.0f, 1.0f);
	mPosition = vec2(0, 0);
}

Camera::~Camera()
{

}

glm::mat4 Camera::Get_Projection()
{
	return mProjection;
}

void Camera::Update(std::function<bool(int)> key_input_function, double delta_time)
{
	if (key_input_function(GLFW_KEY_UP))
	{
		cout << "up" << endl;
		mPosition.y -= 10 * delta_time;
	}
	else if (key_input_function(GLFW_KEY_DOWN))
	{
		cout << "down" << endl;
		mPosition.y += 10 * delta_time;
	}
	else if (key_input_function(GLFW_KEY_LEFT))
	{
		cout << "left" << endl;
		mPosition.x -= 10 * delta_time;
	}
	else if (key_input_function(GLFW_KEY_RIGHT))
	{
		cout << "right" << endl;
		mPosition.x += 10 * delta_time;
	}

	mProjection = glm::ortho(mPosition.x, mPosition.x + static_cast<float>(mWidth),
		mPosition.y + static_cast<float>(mHeight), mPosition.y, -1.0f, 1.0f);
}

void Camera::Update_Viewport(int new_width, int new_height)
{
	mWidth = new_width;
	mHeight = new_height;
	mProjection = glm::ortho(mPosition.x, mPosition.x + static_cast<float>(mWidth),
		mPosition.y + static_cast<float>(mHeight), mPosition.y, -1.0f, 1.0f);
}
