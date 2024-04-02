#pragma once

#ifndef TEXTRENDERING_H_
#define TEXTRENDERING_H_

class TextRendering
{
public:
	TextRendering(const char* file_path, mat4* projection_matrix = 0);
	TextRendering(UINT ID,  mat4* projection_matrix = 0);
	~TextRendering();


	void RenderText(std::string text, float x, float y, float scale, vec3 color);
	void RenderText(std::string text, vec2 pos, float scale, vec3 color);

private:
	Shader* mpShader;
	const char* mpFile_path;
	const mat4* mpProjectionMatrix;

	unsigned int VAO, VBO;

	struct Character {
		unsigned int TextureID;
		ivec2   Size;
		ivec2   Bearing;
		unsigned int Advance;
	};
	std::map<GLchar, Character> Characters;

};


#endif // !TEXTRENDERING_H_
