#include <pch.h>
#include <Game/Object/PuzzleGameBoard.h>
#include <OpenGL/Shader/Shader.h>
#include <Game/Game.h>

PuzzleGameBoard::PuzzleGameBoard(Game* game, int sizeX, int sizeY, int gridX, int gridY) :
	mpGame(game), mSizeX(sizeX), mSizeY(sizeY), mGridX(gridX), mGridY(gridY),
	mpBoardContent(new unique_ptr<BoardContent[]>[mSizeX]),
	mpBoardFrontContent(new BoardContent[mSizeX])
{
	for (int i = 0; i < mSizeX; ++i)
		mpBoardContent[i] = unique_ptr<BoardContent[]>(new BoardContent[mSizeY]);

	mpBoardSprite = make_unique<Sprite>(mpGame->GetTextureShader(), "");
	mpBoardSprite->SetScale(mSizeX * mGridX, mSizeY * mGridY);
	vec2 scale = mpBoardSprite->GetScale();
	mpBoardSprite->SetPosition((*mpGame->GetWindow()->GetWidth() / 2) - (scale.x / 2), 50);
	mpBoardSprite->SetDepth(0.1);
	mBoardPosition = mpBoardSprite->GetPosition();

	for (int x = 0; x < mSizeX; x++)
	{
		for (int y = 0; y < mSizeY; y++)
		{
			mpBoardContent[x][y].Create(0, mpGame->GetTextureShader(), ".\\Image\\Red-Circle.png");
			mpBoardContent[x][y].SetPosition(vec2(
				mBoardPosition.x + (x * mGridX),
				mBoardPosition.y + (y * mGridY)
			));
			mpBoardContent[x][y].GetSprite()->SetDepth(0.2f);
			mpBoardContent[x][y].GetSprite()->SetScale(mGridX, mGridY);
		}
	}

}

PuzzleGameBoard::~PuzzleGameBoard()
{

}

void PuzzleGameBoard::DrawBoard()
{
	mpBoardSprite->Draw();
	for (int x = 0; x < mSizeX; x++)
	{
		for (int y = 0; y < mSizeY; y++)
		{
			mpBoardContent[x][y].Draw();
		}
	}
}

void PuzzleGameBoard::BoardContent::Create(int id, shared_ptr<Shader> shader, const char* path)
{
	mID = id;
	mSprite = make_shared<Sprite>(shader, path);
}

void PuzzleGameBoard::BoardContent::SetID(int id) { mID = id; }
void PuzzleGameBoard::BoardContent::SetPosition(vec2 vec) { mSprite->SetPosition(vec); }


shared_ptr<Sprite> PuzzleGameBoard::BoardContent::GetSprite() { return mSprite; }
int PuzzleGameBoard::BoardContent::GetID() { return mID; }
vec2 PuzzleGameBoard::BoardContent::GetPosition() { return mSprite->GetPosition(); }

void PuzzleGameBoard::BoardContent::Draw()
{
	mSprite->Draw();
}
