#pragma once

#ifndef TEST3DSCENE_H_
#define TEST3DSCENE_H_
#include <Game/Scene/SceneBase.h>

class Model;

class Test3DScene : public SceneBase
{
public:
	SceneCreator(Test3DScene);

	void initializeScene() override;
	void renderScene()override;
	void updateScene()override;
	void releaseScene()override;

private:
	shared_ptr<Model> mpModel;
	shared_ptr<Sprite> mpSprite;


};


#endif // !TEST3DSCENE_H_
