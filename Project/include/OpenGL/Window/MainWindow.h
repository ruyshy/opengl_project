#pragma once

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <OpenGL/Window/OpenGLWindow.h>
#include <OpenGL/VertexBuffer2D/VertexBuffer2D.h>
class Character;

class MainWindow : public OpenGLWindow
{
public:
    MainWindow();
    virtual ~MainWindow();
    void initializeScene() override;
    void renderScene() override;
    void updateScene() override;
    void releaseScene() override;
    void onWindowSizeChanged(int width, int height) override;
    void onMouseButtonPressed(int button, int action) override;


private:
    unique_ptr<Shader> mpCheckboardShader;
    shared_ptr<Shader> mpTextureShader;
    unique_ptr<VertexBufferObject2D> mpCheckboard;
    shared_ptr<Camera> mpCamera;
    shared_ptr<Character> mpCharacter;

public:
    glm::mat4* mpProjectionMatrix;
    shared_ptr<int> mpWidth, mpHeight;

};


#endif // !MAINWINDOW_H_
