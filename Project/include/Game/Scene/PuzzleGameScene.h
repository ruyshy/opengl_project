#pragma once

#ifndef PUZZLEGAMESCENE
#define PUZZLEGAMESCENE

#include <Game/Scene/SceneBase.h>

class PuzzleGameBoard;

class PuzzleGameScene : public SceneBase
{
public:
	SceneCreator(PuzzleGameScene);

	virtual void initializeScene() override;
	virtual void renderScene() override;
	virtual void updateScene() override;
	virtual void releaseScene() override;

	void onMouseButtonPressed(int button, int action) override;

private:
	shared_ptr<PuzzleGameBoard> mpPuzzleGameBoard;

};


#endif // !PUZZLEGAMESCENE
