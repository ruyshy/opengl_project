#pragma once

#ifndef PUZZLEGAMESCENE
#define PUZZLEGAMESCENE

#include <Game/Scene/SceneBase.h>

class PuzzleGameBoard;

class PuzzleGameScene : public SceneBase
{
public:
	SceneCreator(PuzzleGameScene);

	virtual void initializeScene();
	virtual void renderScene();
	virtual void updateScene();
	virtual void releaseScene();

private:
	shared_ptr<PuzzleGameBoard> mpPuzzleGameBoard;

};


#endif // !PUZZLEGAMESCENE
