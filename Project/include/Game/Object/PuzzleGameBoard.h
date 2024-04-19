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
	void SelectObject(double x, double y);

public:
	void DrawBoard();


private:
	int mSizeX, mSizeY, mGridX, mGridY;
	vec2 mBoardPosition;
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
	unique_ptr<BoardContent[]> mpBoardFrontContent;
	unique_ptr<unique_ptr<BoardContent[]>[]> mpBoardContent;
	unique_ptr<Sprite> mpBoardSprite;

	Game* mpGame;

};

#endif // !PUZZLEGAMEBOARD_H_
