#include <pch.h>
#include <OpenGL/Quad/Quad.h>

#include <OpenGL/Shader/Shader.h>
#include <Manager/ResourceManager.h>
#include <rc/shader_resource.h>

#include <OpenGL/Transform2D/Transform2D.h>

Quad::Quad(shared_ptr<Shader> shader, vec2 position, double size)
{
	mpShader = shader;

	mPoints = vector<vec2>();

	model_matrx = mat4(1.0f);

	mColor = vec4(0.6f, 0.6f, 0, 1.0f);

	vec2 r = vec2(position.x + size, position.y + size);
	vec2 e = vec2(position.x - size, position.y + size);
	vec2 c = vec2(position.x + size, position.y - size);
	vec2 t = vec2(position.x - size, position.y - size);

	mPoints.push_back(r);
	mPoints.push_back(e);
	mPoints.push_back(c);
	mPoints.push_back(t);

	unsigned int indices[] = { 0,1,2,2,1,3 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mPoints.size() * sizeof(vec2), mPoints.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);
}

Quad::Quad(shared_ptr<Shader> shader, vec2 position, double width, double height)
{
	mpShader = shader;

	mPoints = vector<vec2>();

	model_matrx = mat4(1.0f);

	mColor = vec4(0.6f, 0.6f, 0, 1.0f);

	vec2 r = vec2(position.x + width, position.y + height);
	vec2 e = vec2(position.x - width, position.y + height);
	vec2 c = vec2(position.x + width, position.y - height);
	vec2 t = vec2(position.x - width, position.y - height);

	mPoints.push_back(r);
	mPoints.push_back(e);
	mPoints.push_back(c);
	mPoints.push_back(t);

	unsigned int indices[] = { 0,1,2,2,1,3 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mPoints.size() * sizeof(vec2), mPoints.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);
}

Quad::~Quad()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	
	NULLPTR_CHECK_DELETE(mpTransfrom);
}

void Quad::SetColor(vec4 color) { mColor = color; }
void Quad::SetColor(float r, float g, float b, float a) { mColor = vec4(r, g, b, a); }

vec4 Quad::GetColor() { return mColor; }

void Quad::Draw()
{
	if (mpTransfrom != nullptr)model_matrx = GetTransform();

	mpShader->use();
	mpShader->setMat4("model_matrx", model_matrx);
	mpShader->setVec4("color", mColor);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Quad::DrawOutline() 
{
	if (mpTransfrom != nullptr)model_matrx = GetTransform();

	mpShader->use();
	mpShader->setMat4("model_matrx", model_matrx);
	mpShader->setVec4("color", mColor);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
}

Transform2DPointerCppMacro(Quad, mpTransfrom);
