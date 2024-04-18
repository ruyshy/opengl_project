#pragma once

#ifndef PUZZLEGAMEBOARD_H_
#define PUZZLEGAMEBOARD_H_

class PuzzleGameBoard
{
public:
	PuzzleGameBoard() = delete;
	PuzzleGameBoard(Game* game, int sizeX, int sizeY, int gridX, int gridY);
	~PuzzleGameBoard();

public:
	void DrawBoard();

private:
	int mSizeX, mSizeY, mGridX, mGridY;
	unique_ptr<unique_ptr<int[]>[]> mpBoardContent;
	unique_ptr<Sprite> mpBoardSprite;

	Game* mpGame;

};

#endif // !PUZZLEGAMEBOARD_H_
