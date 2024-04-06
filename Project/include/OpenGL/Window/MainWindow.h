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

public:
    mat4* GetProjectionMatrix();
    shared_ptr<int> GetWidth();
    shared_ptr<int>GetHeight();

private:
    unique_ptr<Game> mpGame;

private:
    mat4* mpProjectionMatrix;
    shared_ptr<int> mpWidth, mpHeight;

};


#endif // !MAINWINDOW_H_
