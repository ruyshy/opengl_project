#include <pch.h>
#include <Test/TestQuadTreeCollisionScene.h>
#include <Game/Game.h>

#include <OpenGL/QuadTree/QuadTree.h>
#include <OpenGL/Sprite/Sprite.h>
#include <Game/Object/Character/Character.h>
#include <OpenGL/Quad/Quad.h>
#include <utill/TimeMeasure.h>
void TestQuadTreeCollisionScene::initializeScene()
{
    // 현재 4등분하지 않고, 최상위 노드인, 전체 화면 0,0, width, height 기준으로 테스트 TODO: map data struct 4분할한 화면에서 4분활 하여 적용할 예정
    QuadTree::Rect rect(0, 0, 1000,1000);
    mpQuadTree = make_shared<QuadTree>(nullptr, rect, 1);
	mpCharacter = make_shared<Character>(mpGame->GetTextureShader(), ".\\Image\\character.png");
    mpSprite = make_shared<Sprite>(mpGame->GetTextureShader(), "");
    mpSprite->SetPosition(100, 300);
    mpSprite->SetScale(200, 200);

    mSprites = vector<shared_ptr<Sprite>>();
    mSprites.push_back(mpCharacter->GetSprite());
    mSprites.push_back(mpSprite);
}

void TestQuadTreeCollisionScene::renderScene()
{
	mpCharacter->Draw();
    mpSprite->Draw();
}

void TestQuadTreeCollisionScene::updateScene()
{
	mpCharacter->Movement([this](int key) {return mpGame->GetWindow()->keyPressed(key); }, mpGame->GetWindow()->getTimeDelta());

    mpQuadTree->clear();
    for (shared_ptr<Sprite> sprite : mSprites) {
        if (sprite->hasMoved()) {
            mpQuadTree->insert(sprite);
        }
        sprite->update();
    }

    checkCollisions();
}

void TestQuadTreeCollisionScene::releaseScene()
{

}

void TestQuadTreeCollisionScene::checkCollisions()
{
    for (size_t i = 0; i < mSprites.size(); ++i) 
    {
        for (size_t j = i + 1; j < mSprites.size(); ++j)
        {
            if (mSprites[i]->checkCollision(mSprites[j]))
            {
                std::cout << "Sprite " << i << "과 Sprite " << j << "가 충돌했습니다." << std::endl;
            }
        }
    }
}
