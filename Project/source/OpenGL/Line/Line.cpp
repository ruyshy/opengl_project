#include <pch.h>
#include <OpenGL/Line/Line.h>
#include <OpenGL/Shader/Shader.h>

Line::Line(const glm::vec3& start, const glm::vec3& end, std::shared_ptr<Shader> shader)
    : mStart(start), mEnd(end), mpShader(shader) {
    Initialize();
    UpdateVertices();
}

Line::~Line() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Line::Initialize() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Line::UpdateVertices() {
    float vertices[] = {
        mStart.x, mStart.y, mStart.z,
        mEnd.x, mEnd.y, mEnd.z
    };
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line::Draw() {
    mpShader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

void Line::SetStart(const glm::vec3& start) {
    mStart = start;
    UpdateVertices();
}

void Line::SetEnd(const glm::vec3& end) {
    mEnd = end;
    UpdateVertices();
}
