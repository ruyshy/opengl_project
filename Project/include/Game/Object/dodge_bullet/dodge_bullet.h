#pragma once

#ifndef DODGE_BULLET_H_
#define DODGE_BULLET_H_

class dodge_bullet
{
protected:
	dodge_bullet() = delete;
public:
	dodge_bullet(shared_ptr<Shader> shader, const char* filePath, vec2 start, vec2 end, float speed);
	virtual ~dodge_bullet();

	void Movement(double delta_time);
	void Draw();

	shared_ptr<Sprite> GetSprite();

private:
	shared_ptr<Sprite> mpSprite;
	vec2 start, end, direction;
	float mSpeed = 100.0f;
};

#endif // !DODGE_BULLET_H_
