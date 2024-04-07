#pragma once

#ifndef DODGE_BULLET_H_
#define DODGE_BULLET_H_

class dodge_bullet
{
protected:
	dodge_bullet() = delete;
public:
	dodge_bullet(shared_ptr<Shader> shader, const char* filePath, vec2 direction, float speed);
	virtual ~dodge_bullet();

	void Movement(double delta_time);
	void Draw();

	shared_ptr<Sprite> GetSprite();

private:
	shared_ptr<Sprite> mpSprite;
	vec2 mDirection_vector;
	float mSpeed = 100.0f;
};

#endif // !DODGE_BULLET_H_
