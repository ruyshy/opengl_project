#include <pch.h>
#include <Game/Scene/SceneBase.h>

SceneBase::SceneBase(MainWindow* mainWindow) : mpMainWindow(mainWindow), mID(0), mName("")
{

}

SceneBase::SceneBase(MainWindow* mainWindow, unsigned int id, string name) : mpMainWindow(mainWindow), mID(id), mName(name)
{

}

