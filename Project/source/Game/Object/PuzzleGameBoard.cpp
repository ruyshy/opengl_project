#include <pch.h>
#include <Game/Object/PuzzleGameBoard.h>

#include <Game/Game.h>

PuzzleGameBoard::PuzzleGameBoard(Game* game, int sizeX, int sizeY, int gridX, int gridY) :
	mpGame(game), mSizeX(sizeX), mSizeY(sizeY), mGridX(gridX), mGridY(gridY),
	mpBoardContent(new std::unique_ptr<int[]>[mSizeX])
{
	for (int i = 0; i < mSizeX; ++i) 
		mpBoardContent[i] = unique_ptr<int[]>(new int[mSizeY]);

	mpBoardSprite = make_unique<Sprite>(mpGame->GetTextureShader(), "");
	mpBoardSprite->SetScale(mSizeX * mGridX, mSizeY * mGridY);
	vec2 scale = mpBoardSprite->GetScale();
	mpBoardSprite->SetPosition((*mpGame->GetWindow()->GetWidth() / 2) - (scale.x / 2), 50);
	mpBoardSprite->SetDepth(0.1);

}

PuzzleGameBoard::~PuzzleGameBoard()
{

}

void PuzzleGameBoard::DrawBoard()
{
	mpBoardSprite->Draw();
}
