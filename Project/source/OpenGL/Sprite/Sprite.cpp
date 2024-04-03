#include <pch.h>

#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Texture2D/Texture2D.h>
#include <OpenGL/Shader/Shader.h>

#include <OpenGL/VertexBuffer2D/VertexBuffer2D.h>
#include<OpenGL/Transform2D/Transform2D.h>

Sprite::Sprite(shared_ptr<Shader> shader, const char* filename) : mpShader(shader)
{
	mpTextured = make_shared<Texture2D>(TextureSystem::Generate(filename));
	mpVertexBufferObject = make_shared<VertexBufferObject2D>(VertexBufferSystem2D::Generate());
	mpTransformation = make_shared<Transform2D>();
}

//Sprite::Sprite(Shader* shader, string image) : mpShader(shader)
//{
//	mpTextured = new Texture2D(TextureSystem::Generate(image));
//	mpVertexBufferObject = new VertexBufferObject2D(VertexBufferSystem2D::Generate());
//	mpTransformation = new Transform2D();
//}

Sprite::~Sprite()
{
	TextureSystem::Delete(*mpTextured);
	VertexBufferSystem2D::Delete(*mpVertexBufferObject);
}

QuadtreeNode::Rect Sprite::getBounds() const
{
	return QuadtreeNode::Rect(mpTransformation->GetPosition().x, mpTransformation->GetPosition().y, mpTransformation->GetScale().x, mpTransformation->GetScale().y);
}

void Sprite::Draw()
{
	if (!mVisible)return;

	mpShader->use();
	//mpShader->setFloat("zDepth", 1.0f);
	mpShader->setMat4("model_matrx", GetTransform());
	mpTextured->use();
	mpVertexBufferObject->Draw();
}

Transform2DPointerCppMacro(Sprite, mpTransformation);
