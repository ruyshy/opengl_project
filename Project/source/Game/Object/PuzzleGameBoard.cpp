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

	mpBoardSprite = make_unique<Sprite>(mpGame->GetTextureShader(), ".\\Image\\BackGround.png");
	mpBoardSprite->SetScale(mSizeX * mGridX, mSizeY * mGridY);
	vec2 scale = mpBoardSprite->GetScale();
	mpBoardSprite->SetPosition((*mpGame->GetWindow()->GetWidth() / 2) - (scale.x / 2), 50);
	mpBoardSprite->SetDepth(0.1);
	mBoardPosition = mpBoardSprite->GetPosition();

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 499);

	for (int x = 0; x < mSizeX; x++)
	{
		for (int y = 0; y < mSizeY; y++)
		{
			auto randNum = dist(mt);
			if(400 <= randNum && randNum < 500)
				mpBoardContent[x][y].Create(0, mpGame->GetTextureShader(), ".\\Image\\Red-Circle.png");
			else if(300 <= randNum && randNum < 400)
				mpBoardContent[x][y].Create(1, mpGame->GetTextureShader(), ".\\Image\\Blue_Circle.png");
			else if(200 <= randNum && randNum < 300)
				mpBoardContent[x][y].Create(2, mpGame->GetTextureShader(), ".\\Image\\Green_Circle.png");
			else if (100 <= randNum && randNum < 200)
				mpBoardContent[x][y].Create(3, mpGame->GetTextureShader(), ".\\Image\\Pick_Circle.png");
			else if (0 <= randNum && randNum < 100)
				mpBoardContent[x][y].Create(4, mpGame->GetTextureShader(), ".\\Image\\Yellow_Circle.png");
			
			mpBoardContent[x][y].SetPosition(vec2(
				mBoardPosition.x + (x * mGridX),
				mBoardPosition.y + (y * mGridY)));

			mpBoardContent[x][y].GetSprite()->SetDepth(0.2f);
			mpBoardContent[x][y].GetSprite()->SetScale(mGridX, mGridY);
		}
	}

}

PuzzleGameBoard::~PuzzleGameBoard()
{

}

void PuzzleGameBoard::SelectObject(double x, double y)
{
	int xx = static_cast<int>((x - mBoardPosition.x) / mGridX);
	int yy = static_cast<int>((y - mBoardPosition.y) / mGridY);
	if (0 > xx || xx >= mSizeX || 0 > yy || yy >= mSizeY)
		return;
	cout << "xx:" << xx << " yy:" << yy << endl;
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
