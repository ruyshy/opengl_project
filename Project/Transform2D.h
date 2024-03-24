#pragma once

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/gtc/matrix_transform.hpp>

class Transform2D
{
public:
	void* operator new(size_t sz) { return malloc(sz); }
	void operator delete(void* p) noexcept { free(p); }

	glm::vec2 mPosition = glm::vec2(0);
	glm::vec2 mScale = glm::vec2(1);

	float angle = 0;
	bool flipX = false, flipY = false;

	glm::mat4 Get()
	{
		glm::vec2 position = mPosition;
		glm::vec2 scale = mScale;

		if (flipX)
		{
			position = glm::vec2(position.x + scale.x, position.y);
			scale = glm::vec2(-(fabs(scale.x)), scale.y);
		}
		if (flipY)
		{
			position = glm::vec2(position.x, position.y + scale.y);
			scale = glm::vec2(scale.x, -(fabs(scale.y)));
		}

		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(position, 0.0f));
		model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

		model = glm::scale(model, glm::vec3(scale, 1.0f));

		return model;
	}
};

#endif // !TRANSFORM_H_
