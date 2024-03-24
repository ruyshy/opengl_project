#pragma once

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "OpenGLWindow.h"
#include "VertexBuffer2D.h"

class Shader;

class MainWindow : public OpenGLWindow
{
public:
    MainWindow();
    ~MainWindow();
    void initializeScene() override;
    void renderScene() override;
    void updateScene() override;
    void releaseScene() override;
    void onWindowSizeChanged(int width, int height) override;
    void onMouseButtonPressed(int button, int action) override;


private:
    Shader *mpCheckboard;
    VertexBufferObject2D rect;


public:
    glm::mat4* mpProjectionMatrix;
    int* mpWidth, * mpHeight;

};


#endif // !MAINWINDOW_H_
