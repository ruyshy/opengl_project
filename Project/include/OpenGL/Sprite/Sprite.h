#pragma once

#ifndef SPRITE_H_
#define SPRITE_H_

class Transform2D;

class Sprite
{
public:
	Sprite(shared_ptr<Shader> shader, const char* filename);
	~Sprite();

	void Draw();

	QuadtreeNode::Rect getBounds() const;
	bool GetVisible();
	
	shared_ptr<Transform2D> GetTransform();
	vec2 GetPosition();
	vec2 GetCenter();
	vec2 GetScale();
	mat4 GetMatrix();
	float GetAngle();
	bool GetFlipX();
	bool GetFlipY();

	void SetTransform(Transform2D transform);
	void SetVisible(bool visible);
	void SetPosition(vec2 position);
	void SetPosition(float x, float y);
	void SetScale(vec2 scale);
	void SetScale(float x, float y);
	void SetAngle(float angle);
	void SetFlipX(bool flip);
	void SetFlipY(bool flip);

private:
	shared_ptr<VertexBufferObject2D> mpVertexBufferObject;
	shared_ptr<Transform2D> mpTransform;
	bool mVisible = true;

	shared_ptr<Shader> mpShader = nullptr;
	shared_ptr<Texture2D> mpTextured = nullptr;
};

#endif // !SPRITE_H_
