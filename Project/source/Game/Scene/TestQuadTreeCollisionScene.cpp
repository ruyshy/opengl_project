#include <pch.h>
#include <Game/Scene/TestQuadTreeCollisionScene.h>
#include <Game/Game.h>

#include <OpenGL/Sprite/Sprite.h>
#include <Game/Object/Character/Character.h>
#include <OpenGL/Quad/Quad.h>

void TestQuadTreeCollisionScene::initializeScene()
{
    // 현재 4등분하지 않고, 전체 화면 0,0, width, height 기준으로 테스트 TODO: map data struct 4분할한 화면에서 4분활 하여 적용할 예정
    mRootNode = make_shared<QuadtreeNode>(0, 0, *mpGame->GetWindow()->GetWidth(), *mpGame->GetWindow()->GetHeight(), 0, 4, 10);
	mpCharacter = make_shared<Character>(mpGame->GetTextureShader(), ".\\Image\\character.png");
    mpSprite = make_shared<Sprite>(mpGame->GetTextureShader(), "");
    mpSprite->SetPosition(100, 300);
    mpSprite->SetScale(200, 200);


    mRootNode->insert(mpCharacter->GetSprite()->getBounds());
    mRootNode->insert(mpSprite->getBounds());

    mSprites = vector<shared_ptr<Sprite>>();
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
    checkCollisions(*mRootNode, *mpCharacter->GetSprite(), mSprites);
}

void TestQuadTreeCollisionScene::releaseScene()
{

}

void TestQuadTreeCollisionScene::checkCollisions(QuadtreeNode& rootNode, const Sprite& target, std::vector<std::shared_ptr<Sprite>>& potentialCollisions)
{
    std::vector<QuadtreeNode::Rect> candidates = rootNode.queryRange(target.getBounds());

    for (const auto& candidateRect : candidates) 
    {
        for (const auto& potentialCollision : potentialCollisions) 
        {
            if (potentialCollision->getBounds().intersects(candidateRect) && &target != potentialCollision.get())
            {
                std::cout << "Collision detected" << std::endl;
            }
        }
    }
}
