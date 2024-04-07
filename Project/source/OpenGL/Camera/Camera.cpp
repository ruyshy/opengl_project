#include <pch.h>
#include <OpenGL/Camera/Camera.h>
#include <OpenGL/Shader/Shader.h>

Camera::Camera(shared_ptr<Shader> shader, shared_ptr<int> window_width, shared_ptr<int> window_height)
{
	mpShader = shader;
	mpWidth = window_width;
	mpHeight = window_height;

	mProjectionMatrix = ortho(0.0f, static_cast<float>(*mpWidth), static_cast<float>(*mpHeight), 0.0f, -1.0f, 1.0f);

	mPosition = vec3(0, 0, 0);
	mUp = vec3(0, 1, 0);
	mDirection = vec3(0, 0, -10);

	mProjectionMatrix = mat4();
	mViewMatrix = mat4();
}

Camera::~Camera()
{

}

mat4 Camera::GetProjectionMatrix() { return mProjectionMatrix; }
mat4 Camera::GetViewMatrix() { return mViewMatrix; }

vec3 Camera::GetPosition() { return mPosition; }
vec3 Camera::GetUpView() { return mUp; }
vec3 Camera::GetDirection() { return mDirection; }

void Camera::SetPosition(vec3 position) { mPosition = position; }
void Camera::SetDirection(vec3 direction) { mDirection = direction; }
void Camera::SetUpView(vec3 upVector) { mUp = upVector; }


void Camera::Movement(std::function<bool(int)> key_input_function, double delta_time)
{
	if (key_input_function(GLFW_KEY_UP))
		mPosition.y -= 100 * delta_time;
	else if (key_input_function(GLFW_KEY_DOWN))
		mPosition.y += 100 * delta_time;
	else if (key_input_function(GLFW_KEY_LEFT))
		mPosition.x -= 100 * delta_time;
	else if (key_input_function(GLFW_KEY_RIGHT))
		mPosition.x += 100 * delta_time;
}

void Camera::Update()
{
	mProjectionMatrix = ortho(0.0f, static_cast<float>(*mpWidth), static_cast<float>(*mpHeight), 0.0f, -1.0f, 1.0f);

	mViewMatrix = lookAt(
		vec3(mPosition), // camera position
		vec3(mPosition.x + mDirection.x, mPosition.y + mDirection.y, mDirection.z), // camera mDirection
		vec3(mUp)  // camera up flip 0 -1 0
	);

	mpShader->use();
	mpShader->setMat4("projection", mProjectionMatrix);
	mpShader->setMat4("view_matrx", mViewMatrix);
}

