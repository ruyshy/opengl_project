#pragma once

#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite
{
public:
	Sprite(shared_ptr<Shader> shader, const char* filename);
	//Sprite(Shader* shader, string image);

	~Sprite();

	//QuadtreeNode::Rect getBounds() const;
	void Draw();

	Transform2DHeaderMacro();

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() { return mVisible; }

private:
	shared_ptr<VertexBufferObject2D> mpVertexBufferObject;
	shared_ptr<Transform2D> mpTransformation;
	bool mVisible = true;

	shared_ptr<Shader> mpShader = nullptr;
	shared_ptr<Texture2D> mpTextured = nullptr;
};

#endif // !SPRITE_H_
