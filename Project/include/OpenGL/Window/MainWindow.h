#pragma once

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <OpenGL/Window/OpenGLWindow.h>
#include <OpenGL/VertexBuffer2D/VertexBuffer2D.h>

class Camera;
class Sprite;

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
    unique_ptr<Shader> mpCheckboard;
    Shader* mpTextureShader;
    Sprite* mpSprite;
    VertexBufferObject2D rect;
    unique_ptr<Camera> mpCamera;


public:
    glm::mat4* mpProjectionMatrix;
    int* mpWidth, * mpHeight;

};


#endif // !MAINWINDOW_H_
