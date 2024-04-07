#include <pch.h>

#include <Game/Game.h>
#include <Game/Score/Score_dodge.h>

#include <Manager/ResourceManager.h>
#include <rc/font_resource.h>

Score_dodge::Score_dodge(Game* game)
{
	mpGame = game;
	//IDB_FONT_ARIAL
	mpTextRendering = make_unique<TextRendering>(IDB_FONT_ARIAL,
		mpGame->GetWindow()->getOrthoProjectionMatrix(),
		mpGame->GetCamera()->GetViewMatrix(),
		vec2(0.0f, *mpGame->GetWindow()->GetHeight() - 25),
		0.5f);
}

Score_dodge::~Score_dodge()
{
}

string Score_dodge::CutOnSpecificDecimalPt(string num, int pos)
{
	return num.substr(0, num.find('.') + pos + 1);
}

void Score_dodge::Draw(float score)
{
	mpTextRendering->RenderText(score_text + CutOnSpecificDecimalPt(to_string(score), 2),
		0.0f,
		*mpGame->GetWindow()->GetHeight() - 25,
		0.5f,
		vec3(1, 1, 0));

}