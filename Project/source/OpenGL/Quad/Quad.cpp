#include <pch.h>
#include <OpenGL/Quad/Quad.h>

#include <OpenGL/Shader/Shader.h>
#include <Manager/ResourceManager.h>
#include <rc/shader_resource.h>

#include <OpenGL/Transform2D/Transform2D.h>

Quad::Quad(shared_ptr<Shader> shader, vec2 position, double size)
{
	mpShader = shader;
	mColor = glm::vec4(1.0f); // 기본 색상은 흰색
	model_matrx = glm::mat4(1.0f);

	// 사각형의 정점 데이터 설정
	float vertices[] = {
		position.x + size / 2.0f, position.y + size / 2.0f, 0.0f, // 우상단
		position.x - size / 2.0f, position.y + size / 2.0f, 0.0f, // 좌상단
		position.x - size / 2.0f, position.y - size / 2.0f, 0.0f, // 좌하단
		position.x + size / 2.0f, position.y - size / 2.0f, 0.0f  // 우하단
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 위치 데이터를 attribute 0에 링크
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Quad::Quad(shared_ptr<Shader> shader, glm::vec2 position, float width, float height) {
	mpShader = shader;
	mColor = glm::vec4(1.0f); // 기본 색상은 흰색
	model_matrx = glm::mat4(1.0f);

	// 사각형의 정점 데이터 설정
	float vertices[] = {
		position.x + width / 2.0f, position.y + height / 2.0f, 0.0f, // 우상단
		position.x - width / 2.0f, position.y + height / 2.0f, 0.0f, // 좌상단
		position.x - width / 2.0f, position.y - height / 2.0f, 0.0f, // 좌하단
		position.x + width / 2.0f, position.y - height / 2.0f, 0.0f  // 우하단
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 위치 데이터를 attribute 0에 링크
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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
	mpShader->setVec4("color", mColor);
	mpShader->setMat4("model_matrx", model_matrx);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Quad::DrawOutline() 
{
	if (mpTransfrom != nullptr)model_matrx = GetTransform();
	mpShader->use();
	mpShader->setVec4("color", mColor);
	mpShader->setMat4("model_matrx", model_matrx);

	glLineWidth(3.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
}

Transform2DPointerCppMacro(Quad, mpTransfrom);
