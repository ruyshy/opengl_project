#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Camera
{
public:
	Camera(shared_ptr<int> window_width, shared_ptr<int> window_height);
	~Camera();

	glm::mat4 Get_Projection();

	void SetPosition(glm::vec2 position);
	void Update();

	void Key_Update(std::function<bool(int)> key_input_function, double delta_time);

private:
	glm::mat4 mProjection;
	glm::vec2 mPosition;
	shared_ptr<const int> mpWidth, mpHeight;
};


#endif // !CAMERA_H_

