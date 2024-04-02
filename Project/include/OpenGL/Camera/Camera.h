#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Camera
{
public:
	Camera(shared_ptr<Shader> shader, shared_ptr<int> window_width, shared_ptr<int> window_height);
	~Camera();

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
	void SetPosition(glm::vec3 position);
	void Update();

	void Key_Update(std::function<bool(int)> key_input_function, double delta_time);

private:
	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;
	const glm::mat4 _ModelMatrix = glm::mat4(1.0);
	glm::vec3 mPosition;
	shared_ptr<Shader> mpShader;
	shared_ptr<const int> mpWidth, mpHeight;
};


#endif // !CAMERA_H_

