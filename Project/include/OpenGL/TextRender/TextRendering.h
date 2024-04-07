#pragma once

#ifndef TEXTRENDERING_H_
#define TEXTRENDERING_H_

class TextRendering
{
public:
	TextRendering(UINT ID, mat4 projection_matrix, mat4 view_matrix, vec2 position, float scale);
	~TextRendering();

	void SetPosition(vec2 position);
	void SetSize(vec2 size);

	vec2 GetPosition();
	vec2 GetSize();

	void RenderText(std::string text, glm::vec3 color);
	void RenderText(std::string text, float x, float y, glm::vec3 color);
	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
	void RenderText(std::string text, vec2 pos, float scale, glm::vec3 color);

private:
	Shader* mpShader;
	const char* mpFile_path;
	mat4 mpProjectionMatrix;
	mat4 mpViewMatrix;

	unsigned int VAO, VBO;

	struct Character {
		unsigned int TextureID;
		glm::ivec2   Size;
		glm::ivec2   Bearing;
		unsigned int Advance;
	};
	std::map<GLchar, Character> Characters;

	float mTextScale = 1.0f;
	vec2 mPosition = vec2(0, 0), mSize = vec2(0, 0);

};


#endif // !TEXTRENDERING_H_
