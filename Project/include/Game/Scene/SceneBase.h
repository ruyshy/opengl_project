#pragma once

#ifndef SCENEBASE_H_
#define SCENEBASE_H_

class SceneBase
{
public:
	SceneBase() = delete;
	SceneBase(MainWindow* mainWindow);
	SceneBase(MainWindow* mainWindow, unsigned int id, string name);

	virtual void initializeScene() {}
	virtual void renderScene() {}
	virtual void updateScene() {}
	virtual void releaseScene() {}

private:
	const MainWindow* mpMainWindow;
	unsigned int mID;
	string mName;

};

#endif // !SCENEBASE_H_
