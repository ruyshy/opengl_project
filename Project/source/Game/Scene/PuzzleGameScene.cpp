#include <pch.h>
#include <Game/Game.h>
#include <Game/Object/PuzzleGameBoard.h>

#include <Game/Scene/PuzzleGameScene.h>

void PuzzleGameScene::initializeScene()
{
	mpPuzzleGameBoard = make_shared<PuzzleGameBoard>(mpGame,20, 20, 25, 25);
	//mpGame->GetWindow()->onMouseButtonPressed();
}

void PuzzleGameScene::renderScene()
{
	mpPuzzleGameBoard->DrawBoard();

}

void PuzzleGameScene::updateScene()
{

}

void PuzzleGameScene::releaseScene()
{

}

void PuzzleGameScene::onMouseButtonPressed(int button, int action)
{
	if (action == 1)
	{
		mpPuzzleGameBoard->SelectObject(*mpGame->GetWindow()->GetMouseX(), *mpGame->GetWindow()->GetMouseY());
	}
}
