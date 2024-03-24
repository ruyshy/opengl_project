#pragma once

#ifndef SPRITE_H_
#define SPRITE_H_

#include "Transform2D_Macro.h"

class Texture2D;
class Shader;
class VertexBufferObject2D;

class Sprite
{
public:
	Sprite(Shader* shader, const char* filename);
	Sprite(Shader* shader, string image);

	~Sprite();

	void Draw();

	Transform2DHeaderMacro();

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() { return mVisible; }

private:
	VertexBufferObject2D* mpVertexBufferObject;
	Transform2D* mpTransformation;
	bool mVisible = true;

	Shader* mpShader = nullptr;
	Texture2D* mpTextured = nullptr;
};

#endif // !SPRITE_H_
