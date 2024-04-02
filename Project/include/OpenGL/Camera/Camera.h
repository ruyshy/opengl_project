#pragma once

#ifndef CAMERA_H_
#define CAMERA_H_

class Camera
{
public:
	Camera(shared_ptr<Shader> shader, shared_ptr<int> window_width, shared_ptr<int> window_height);
	~Camera();

	mat4 GetProjectionMatrix();
	mat4 GetViewMatrix();
	
	vec3 GetPosition();
	vec3 GetUpView();
	vec3 GetDirection();

	void SetPosition(vec3 position);
	void SetDirection(vec3 direction);
	void SetUpView(vec3 upVector);

	void Update();

	void Key_Update(std::function<bool(int)> key_input_function, double delta_time);

private:
	mat4 mProjectionMatrix;
	mat4 mViewMatrix;
	vec3 mPosition;
	vec3 mUp;
	vec3 mDirection;

	shared_ptr<Shader> mpShader;
	shared_ptr<const int> mpWidth, mpHeight;
};


#endif // !CAMERA_H_

