#pragma once

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

class Player;

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

    void Render();

public:
    mat4* GetProjectionMatrix();
    shared_ptr<int> GetWidth();
    shared_ptr<int>GetHeight();
    shared_ptr<double> GetMouseX();
    shared_ptr<double> GetMouseY();

private:
    unique_ptr<Game> mpGame;

private:
    mat4* mpProjectionMatrix;
    shared_ptr<int> mpWidth, mpHeight;
    shared_ptr<double> mpMouseX, mpMouseY;
};


#endif // !MAINWINDOW_H_
