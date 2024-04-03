#include <pch.h>
#include <Game/Scene/TestScene.h>
#include <Game/Game.h>
#include <OpenGL/Sprite/Sprite.h>
#include <Game/Object/Character/Character.h>
#include <OpenGL/Quad/Quad.h>

void TestScene::initializeScene()
{
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

void TestScene::renderScene()
{
	mpCharacter->Draw();
    mpSprite->Draw();
}

void TestScene::updateScene()
{
	mpCharacter->Movement([this](int key) {return mpGame->GetWindow()->keyPressed(key); }, mpGame->GetWindow()->getTimeDelta());
    checkCollisions(*mRootNode, *mpCharacter->GetSprite(), mSprites);
}

void TestScene::releaseScene()
{

}

void TestScene::checkCollisions(QuadtreeNode& rootNode, const Sprite& target, std::vector<std::shared_ptr<Sprite>>& potentialCollisions)
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
