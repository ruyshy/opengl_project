#pragma once

#ifndef SPRITE_H_
#define SPRITE_H_

#include <OpenGL/QuadTree/QuadTreeNode.h>

class Sprite
{
public:
	Sprite(Shader* shader, const char* filename);
	//Sprite(Shader* shader, string image);

	~Sprite();

	//QuadtreeNode::Rect getBounds() const;
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
