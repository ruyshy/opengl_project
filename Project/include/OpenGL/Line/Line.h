#pragma once

#ifndef LINE_H_
#define LINE_H_

class Line {
public:
    Line(const glm::vec3& start, const glm::vec3& end, std::shared_ptr<Shader> shader);
    ~Line();

    void Draw();
    void SetStart(const glm::vec3& start);
    void SetEnd(const glm::vec3& end);

private:
    std::shared_ptr<Shader> mpShader;
    GLuint VAO, VBO;
    glm::vec3 mStart, mEnd;

    void Initialize();
    void UpdateVertices();
};

#endif // LINE_H_
