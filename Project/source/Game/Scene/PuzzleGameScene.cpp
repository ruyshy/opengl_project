#include <pch.h>
#include <Game/Game.h>
#include <Game/Object/PuzzleGameBoard.h>

#include <Game/Scene/PuzzleGameScene.h>

void PuzzleGameScene::initializeScene()
{
	mpPuzzleGameBoard = make_shared<PuzzleGameBoard>(mpGame,20, 20, 25, 25);

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
