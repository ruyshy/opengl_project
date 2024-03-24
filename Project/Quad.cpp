#include "pch.h"
#include "Quad.h"

#include "Shader.h"
#include "ResourceManager.h"
#include "shader_resource.h"

#include "Transform2D.h"

Quad::Quad()
{
	mpTransfrom = new Transform2D();

	mpShader = new Shader(
		ResourceManager::GetResourceString(IDR_NORMAL_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_NORMAL_FS, Resource::SHADER)
	);

	points = vector<vec2>();

	projection_matrix = mat4(1.0f);
	model_matrx = mat4(1.0f);

	Width = 1.0f;
	Color = vec4(1.0f, 0.0f, 0.0f, 0.75f);

	vec2 r = vec2(0, 0);
	vec2 e = vec2(0, 1);
	vec2 c = vec2(1, 0);
	vec2 t = vec2(1, 1);

	points.push_back(r);
	points.push_back(e);
	points.push_back(c);
	points.push_back(t);

	unsigned int indices[] = { 0,1,2,2,1,3 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(points), points.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);
}

Quad::Quad(vec2 position, double width)
{
	mpShader = new Shader(
		ResourceManager::GetResourceString(IDR_NORMAL_VS, Resource::SHADER),
		ResourceManager::GetResourceString(IDR_NORMAL_FS, Resource::SHADER)
	);

	points = vector<vec2>();

	projection_matrix = mat4(1.0f);
	model_matrx = mat4(1.0f);

	Color = vec4(0.6f, 0.6f, 0, 1.0f);

	Width = width / 2.0f;
	double Height = Width / 4.0f;

	vec2 r = vec2(position.x + Width, position.y + Height);
	vec2 e = vec2(position.x - Width, position.y + Height);
	vec2 c = vec2(position.x + Width, position.y - Height);
	vec2 t = vec2(position.x - Width, position.y - Height);

	points.push_back(r);
	points.push_back(e);
	points.push_back(c);
	points.push_back(t);

	unsigned int indices[] = { 0,1,2,2,1,3 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(points), points.data(), GL_STATIC_DRAW);

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
	NULLPTR_CHECK_DELETE(mpShader);
}

void Quad::SetColor(vec4 color) { Color = color; }
void Quad::SetColor(float r, float g, float b, float a) { Color = vec4(r, g, b, a); }
vec4 Quad::GetColor() { return Color; }

void Quad::Draw()
{
	if (mpTransfrom != nullptr)model_matrx = GetTransform();

	mpShader->use();
	mpShader->setMat4("projection", projection_matrix);
	mpShader->setMat4("model_matrx", model_matrx);
	mpShader->setVec4("color", Color);



	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Quad::Draw(mat4 _projection_matrix)
{
	projection_matrix = _projection_matrix;
	if (mpTransfrom != nullptr)model_matrx = GetTransform();

	mpShader->use();
	mpShader->setMat4("projection", projection_matrix);
	mpShader->setMat4("model_matrx", model_matrx);
	mpShader->setVec4("color", Color);


	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Transform2DPointerCppMacro(Quad, mpTransfrom);
