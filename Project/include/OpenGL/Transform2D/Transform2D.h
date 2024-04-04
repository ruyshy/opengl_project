#pragma once

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

class Transform2D
{
public:
	void* operator new(size_t sz) { return malloc(sz); }
	void operator delete(void* p) noexcept { free(p); }

private:
	vec2 mPosition = vec2(0);
	vec2 mScale = vec2(1);

	float mAngle = 0;
	bool mFlipX = false, mFlipY = false;

public:
	mat4 Get()
	{
		vec2 position = mPosition;
		vec2 scale = mScale;

		if (mFlipX)
		{
			position = vec2(position.x + scale.x, position.y);
			scale = vec2(-(fabs(scale.x)), scale.y);
		}
		if (mFlipY)
		{
			position = vec2(position.x, position.y + scale.y);
			scale = vec2(scale.x, -(fabs(scale.y)));
		}

		mat4 model = mat4(1.0f);

		model = translate(model, vec3(position, 0.0f));
		model = translate(model, vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
		model = rotate(model, radians(mAngle), vec3(0.0f, 0.0f, 1.0f));
		model = translate(model, vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

		model = glm::scale(model, vec3(scale, 1.0f));

		return model;
	}

	vec2 GetPosition() { return mPosition; }
	vec2 GetCenter() { return vec2((mPosition.x - (mScale.x / 2)), (mPosition.y - (mScale.y / 2))); }
	vec2 GetScale() { return mScale; }
	float GetAngle() { return mAngle; }
	bool GetFlipX() { return mFlipX; }
	bool GetFlipY() { return mFlipY; }

	void SetPosition(vec2 position) { mPosition = position; }
	void SetScale(vec2 scale) { mScale = scale; }
	void SetAngle(float angle) { mAngle = angle; }
	void SetFlipX(bool flip) { mFlipX = flip; }
	void SetFlipY(bool flip) { mFlipY = flip; }

};

#endif // !TRANSFORM_H_
