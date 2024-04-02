#include <pch.h>
#include <OpenGL/Camera/Camera.h>
#include <OpenGL/Shader/Shader.h>

Camera::Camera(shared_ptr<Shader> shader, shared_ptr<int> window_width, shared_ptr<int> window_height)
{
	mpShader = shader;
	mpWidth = window_width;
	mpHeight = window_height;

	mProjectionMatrix = glm::ortho(0.0f, static_cast<float>(*mpWidth), static_cast<float>(*mpHeight), 0.0f, -1.0f, 1.0f);

	mPosition = vec3(0, 0, 0);
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetProjectionMatrix() { return mProjectionMatrix; }
glm::mat4 Camera::GetViewMatrix() { return mViewMatrix; }

void Camera::SetPosition(glm::vec3 position)
{

}

void Camera::Key_Update(std::function<bool(int)> key_input_function, double delta_time)
{
	if (key_input_function(GLFW_KEY_UP))
		mPosition.y -= 100 * delta_time;
	else if (key_input_function(GLFW_KEY_DOWN))
		mPosition.y += 100 * delta_time;
	else if (key_input_function(GLFW_KEY_LEFT))
		mPosition.x -= 100 * delta_time;
	else if (key_input_function(GLFW_KEY_RIGHT))
		mPosition.x += 100 * delta_time;

	//mpShader->use();
	//mpShader->setMat4("view_matrx", mViewMatrix);
}

void Camera::Update()
{
	mProjectionMatrix = glm::ortho(0.0f, static_cast<float>(*mpWidth), static_cast<float>(*mpHeight), 0.0f, -1.0f, 1.0f);

	mViewMatrix = glm::lookAt(
		glm::vec3(mPosition), // camera position
		glm::vec3(mPosition.x, mPosition.y, -10), // camera direction
		glm::vec3(0, 1, 0)  // camera up flip 0 -1 0
	);

	mpShader->use();
	mpShader->setMat4("projection", mProjectionMatrix);
	mpShader->setMat4("view_matrx", mViewMatrix);
}

