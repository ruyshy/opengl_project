#include <pch.h>
#include <Game/Scene/Bullets_dodge_Scene.h>
#include <Game/Game.h>
#include <Game/Object/Player/Player.h>
#include <OpenGL/Quad/Quad.h>
#include <utill/TimeMeasure.h>

void Bullets_dodge_Scene::initializeScene()
{
    QuadTree::Rect rect(0, 0, *mpGame->GetWindow()->GetWidth(), *mpGame->GetWindow()->GetHeight());
    mpQuadTree = make_shared<QuadTree>(nullptr, rect, 0);
    mpBackGround = make_shared<Sprite>(mpGame->GetTextureShader(), ".\\Image\\back_ground.png");
    mpBackGround->SetPosition(0,0);
    mpBackGround->SetScale(*mpGame->GetWindow()->GetWidth(), *mpGame->GetWindow()->GetHeight());

	mpPlayer = make_shared<Player>(mpGame->GetTextureShader(), ".\\Image\\Player.png");
    mpPlayer->GetSprite()->SetScale(vec2(50, 50));
    mpPlayer->GetSprite()->SetPosition(vec2(*mpGame->GetWindow()->GetWidth() / 2, *mpGame->GetWindow()->GetHeight() / 2) - mpPlayer->GetSprite()->GetScale());
    mpPlayer->GetSprite()->SetDepth(0.1);
    mpPlayer->SetSpeed(250.0f);

    mSprites = vector<shared_ptr<Sprite>>();
    mSprites.push_back(mpPlayer->GetSprite());

}

void Bullets_dodge_Scene::renderScene()
{
    mpBackGround->Draw();
	mpPlayer->Draw();
}

void Bullets_dodge_Scene::updateScene()
{
	mpPlayer->Movement([this](int key) {return mpGame->GetWindow()->keyPressed(key); }, mpGame->GetWindow()->getTimeDelta());

    mpQuadTree->clear();
    for (shared_ptr<Sprite> sprite : mSprites) 
    {
        if (sprite->hasMoved()) 
            mpQuadTree->insert(sprite);
        sprite->update();
    }
    mpQuadTree->subdivide();
    checkCollisions(mpQuadTree);
}

void Bullets_dodge_Scene::releaseScene()
{

}

void Bullets_dodge_Scene::checkCollisions(shared_ptr<QuadTree> quadtree) {
    std::vector<shared_ptr<Sprite>> potentialCollisions;

    for (auto& sprite : mSprites) {
        potentialCollisions.clear();
        quadtree->retrieve(potentialCollisions, sprite);

        for (auto& target : potentialCollisions) {
            if (sprite != target && sprite->checkCollision(target)) {
                std::cout << "Sprite " << sprite->GetName() << "�� Sprite " << target->GetName() << "�� �浹�߽��ϴ�." << std::endl;
            }
        }
    }
}

void Bullets_dodge_Scene::checkPlayerCollsions(shared_ptr<QuadTree> quadtree)
{
    auto player = mpPlayer->GetSprite();

    for (auto& sprite : mSprites) 
    {
        if (!sprite->hasScreen())
            continue;

        if (sprite->checkCollision(player)) {
            cout << player->GetName() << " && " << sprite->GetName() << "�浹�߽��ϴ�."  << endl;
        }
    }
}