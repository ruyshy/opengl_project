#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Camera
{
public:
	Camera(int window_width, int window_height);
	~Camera();

	glm::mat4 Get_Projection();

	void Update(std::function<bool(int)> key_input_function);
	void Update_Viewport(int new_width, int new_height);

private:
	glm::mat4 projection;
	glm::vec2 position;
};


#endif // !CAMERA_H_

