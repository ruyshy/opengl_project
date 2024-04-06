#pragma once

#ifndef SPRITE_H_
#define SPRITE_H_
#include <Game/Object/ObjectBase.h>

class Sprite : public ObjectBase
{
public:
	Sprite(shared_ptr<Shader> shader, const char* filename);
	Sprite(shared_ptr<Shader> shader, const char* filename, float x, float y, float xx, float yy);
	~Sprite();


	void Draw();

	bool checkCollision(shared_ptr<Sprite> other);
	bool hasMoved();
	bool hasScreen();
	bool hasScreen(float width, float height);
	void update();

	bool GetVisible();
	
	shared_ptr<Transform2D> GetTransform();
	vec2 GetPosition();
	vec2 GetCenter();
	vec2 GetScale();
	mat4 GetMatrix();
	float GetAngle();
	bool GetFlipX();
	bool GetFlipY();

	vec4 GetScreen();

	void SetTransform(Transform2D transform);
	void SetVisible(bool visible);
	void SetPosition(vec2 position);
	void SetPosition(float x, float y);
	void SetDepth(float value);
	void SetScale(vec2 scale);
	void SetScale(float x, float y);
	void SetAngle(float angle);
	void SetFlipX(bool flip);
	void SetFlipY(bool flip);

private:
	shared_ptr<VertexBufferObject2D> mpVertexBufferObject;
	shared_ptr<Transform2D> mpTransform;
	float mScreenX, mScreenY, mScreenW, mScreenH ;
	float mLastX, mLastY;
	float mZDepth = 0.0f;

	bool mVisible = true;

	shared_ptr<Shader> mpShader = nullptr;
	shared_ptr<Texture2D> mpTextured = nullptr;
};

#endif // !SPRITE_H_
