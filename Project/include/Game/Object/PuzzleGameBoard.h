#pragma once

#ifndef PUZZLEGAMEBOARD_H_
#define PUZZLEGAMEBOARD_H_

class Shader;

class PuzzleGameBoard
{
public:
	PuzzleGameBoard() = delete;
	PuzzleGameBoard(Game* game, int sizeX, int sizeY, int gridX, int gridY);
	~PuzzleGameBoard();

public:
	void SelectObject(int& x, int& y);

	vec2 GetPosition();
	vec2 GetScale();
	int GetSizeX();
	int GetSizeY();
	int GetGridX();
	int GetGridY();
	bool GetSelect();

public:
	void DrawBoard();

public:
	void ChangeContent(int x, int y, int xx, int yy);

private:
	int mSizeX, mSizeY, mGridX, mGridY;
	double mMoveSpeed;
	bool mSelect, mMovement;
	vec2 mBoardPosition;
	vec2 mBoardScale;
	struct BoardContent
	{
		int mID = 0;
		shared_ptr<Sprite> mSprite = nullptr;

		void Create(int id, shared_ptr<Shader> shader, const char* path);
		void SetID(int id);
		void SetPosition(vec2 vec);

		shared_ptr<Sprite> GetSprite();
		int GetID();
		vec2 GetPosition();

		void Draw();
	};
	shared_ptr<BoardContent[]> mpBoardFrontContent;
	shared_ptr<shared_ptr<BoardContent[]>[]> mpBoardContent;
	shared_ptr<Sprite> mpBoardSprite;
	shared_ptr<Sprite> mpBoardSelectSprite;
	Game* mpGame;

};

#endif // !PUZZLEGAMEBOARD_H_
