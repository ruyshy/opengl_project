#pragma once

#ifndef SCENEBASE_H_
#define SCENEBASE_H_

#define SceneCreator(class_name)																		\
class_name(Game* game) : SceneBase(game)														\
{initializeScene();}																								\
class_name(Game* game, unsigned int id, string name) : SceneBase(game, id, name)	\
{initializeScene();}																								\
virtual ~class_name(){ releaseScene(); }																	\

class SceneBase
{
public:
	SceneBase() = delete;
	SceneBase(Game* game);
	SceneBase(Game* game, unsigned int id, string name);
	virtual ~SceneBase() { releaseScene(); }

	virtual void initializeScene() {}
	virtual void renderScene() {}
	virtual void updateScene() {}
	virtual void releaseScene() {}

protected:
	Game* mpGame;
	unsigned int mID;
	string mName;

};

#endif // !SCENEBASE_H_
