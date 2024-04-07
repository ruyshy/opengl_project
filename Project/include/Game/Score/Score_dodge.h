#pragma once

#ifndef SCORE_DODGE_H_
#define SCORE_DODGE_H_


class Score_dodge
{
public:
	Score_dodge() = delete;
	Score_dodge(Game* game);
	~Score_dodge();

	string CutOnSpecificDecimalPt(string num, int pos);

	void Draw(float score);

private:
	unique_ptr<TextRendering>mpTextRendering;
	Game* mpGame;
	const string score_text = "Score ";
};

#endif // !SCORE_DODGE_H_
