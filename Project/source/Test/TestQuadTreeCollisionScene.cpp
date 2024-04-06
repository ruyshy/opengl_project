#include <pch.h>
#include <Test/TestQuadTreeCollisionScene.h>
#include <Game/Game.h>
#include <Game/Object/Player/Player.h>
#include <OpenGL/Quad/Quad.h>
#include <utill/TimeMeasure.h>

void TestQuadTreeCollisionScene::initializeScene()
{
    QuadTree::Rect rect(0, 0, *mpGame->GetWindow()->GetWidth(), *mpGame->GetWindow()->GetHeight());
    mpQuadTree = make_shared<QuadTree>(nullptr, rect, 0);
	mpPlayer = make_shared<Player>(mpGame->GetTextureShader(), ".\\Image\\character.png");
    mpPlayer->SetSpeed(300.0f);

    mpSprite = make_shared<Sprite>(mpGame->GetTextureShader(), "");
    mpSprite->SetPosition(100, 300);
    mpSprite->SetScale(200, 200);

    mSprites = vector<shared_ptr<Sprite>>();
    mSprites.push_back(mpPlayer->GetSprite());
    mSprites.push_back(mpSprite);
}

void TestQuadTreeCollisionScene::renderScene()
{
	mpPlayer->Draw();
    mpSprite->Draw();
}

void TestQuadTreeCollisionScene::updateScene()
{
	mpPlayer->Movement([this](int key) {return mpGame->GetWindow()->keyPressed(key); }, mpGame->GetWindow()->getTimeDelta());

    mpQuadTree->clear();
    for (shared_ptr<Sprite> sprite : mSprites) {
        if (sprite->hasMoved()) {
            mpQuadTree->insert(sprite);
        }
        sprite->update();
    }
    mpQuadTree->subdivide();
    checkCollisions(mpQuadTree);
}

void TestQuadTreeCollisionScene::releaseScene()
{

}

void TestQuadTreeCollisionScene::checkCollisions(shared_ptr<QuadTree> quadtree) {
    std::vector<shared_ptr<Sprite>> potentialCollisions;

    for (auto& sprite : mSprites) {
        potentialCollisions.clear();
        quadtree->retrieve(potentialCollisions, sprite);

        for (auto& target : potentialCollisions) {
            if (sprite != target && sprite->checkCollision(target)) {
                std::cout << "Sprite " << sprite->GetName() << "와(과) Sprite " << target->GetName() << "가 충돌했습니다." << std::endl;
            }
        }
    }
}