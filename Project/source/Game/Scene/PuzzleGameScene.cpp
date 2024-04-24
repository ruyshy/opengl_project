#include <pch.h>
#include <Game/Game.h>
#include <Game/Object/PuzzleGameBoard.h>

#include <Game/Scene/PuzzleGameScene.h>

void PuzzleGameScene::initializeScene()
{
	mpPuzzleGameBoard = make_shared<PuzzleGameBoard>(mpGame,15, 15, 30, 30);
	//mpGame->GetWindow()->onMouseButtonPressed();
}

void PuzzleGameScene::renderScene()
{
	mpPuzzleGameBoard->DrawBoard();

}

void PuzzleGameScene::updateScene()
{
	mpPuzzleGameBoard->ChangeContent(mPreviousX, mPreviousY, mPosX, mPosY);
	bool a= mpPuzzleGameBoard->checkConsecutiveThree();
	cout << "a" << a << endl;
}

void PuzzleGameScene::releaseScene()
{

}

void PuzzleGameScene::onMouseButtonPressed(int button, int action)
{
	mPosX = *mpGame->GetWindow()->GetMouseX();
	mPosY = *mpGame->GetWindow()->GetMouseY();
	if (action == 1)
	{
		mpPuzzleGameBoard->SelectObject(mPosX, mPosY);
		if (mpPuzzleGameBoard->GetSelect())
		{
			mPreviousX = mPosX;
			mPreviousY = mPosY;
		}
	}
	//else if (action == 0)
	//	mpPuzzleGameBoard->SelectObject(mPosX, mPosY);
}
