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
    
    boxMin = vec2(rect.x, rect.y);
    boxMax = vec2(rect.width, rect.height);
    
    front_vec = vec4(rect.x - 5, rect.y - 5, rect.x + 5, rect.y + 5);
    back_vec = vec4(rect.width + 5, rect.height + 5, rect.width + 5, rect.height + 5);
    right_vec = vec4(rect.x - 5, rect.y - 5, rect.x, rect.height + 5);
    left_vec = vec4(rect.width + 5, rect.y - 5, rect.width + 5, rect.height + 5);

    mpBackGround = make_shared<Sprite>(mpGame->GetTextureShader(), ".\\Image\\back_ground.png");
    mpBackGround->SetPosition(0,0);
    mpBackGround->SetScale(*mpGame->GetWindow()->GetWidth(), *mpGame->GetWindow()->GetHeight());
    mpScore = make_unique<Score_dodge>(mpGame);

	mpPlayer = make_shared<Player>(mpGame->GetTextureShader(), ".\\Image\\Player.png");
    mpPlayer->GetSprite()->SetScale(vec2(50, 50));
    mpPlayer->GetSprite()->SetPosition(vec2(*mpGame->GetWindow()->GetWidth() / 2, *mpGame->GetWindow()->GetHeight() / 2) - mpPlayer->GetSprite()->GetScale());
    mpPlayer->GetSprite()->SetDepth(0.1);
    mpPlayer->SetSpeed(250.0f);

    mSprites = vector<shared_ptr<Sprite>>();
}

void Bullets_dodge_Scene::renderScene()
{
    mpBackGround->Draw();

    for (int x = 0; x < mBullet_count; x++)
        mpBullet[x]->Draw();
	mpPlayer->Draw();


    mpScore->Draw(mScore);
}

void Bullets_dodge_Scene::updateScene()
{
    double timer = mpGame->GetWindow()->getTimeDelta();
	mpPlayer->Movement([this](int key) {return mpGame->GetWindow()->keyPressed(key); }, timer);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    mBulletCreateTimer += (timer / 2.0f);
    mScore += timer;
    if (mBulletCreateTimer >= mBulletCreateTime)
    {
        bullet_create();
        mBulletCreateTimer = 0;
    }

    for (int x = 0; x < mBullet_count; x++) 
    {
        mpBullet[x]->Movement(mpGame->GetWindow()->getTimeDelta());
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    mpQuadTree->clear();
    for (shared_ptr<Sprite> sprite : mSprites) 
    {
        if (sprite->hasMoved()) 
            mpQuadTree->insert(sprite);
        sprite->update();
    }
    mpQuadTree->subdivide();
    checkPlayerCollsions(mpQuadTree);
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
                std::cout << "Sprite " << sprite->GetName() << "와 Sprite " << target->GetName() << "가 충돌했습니다." << std::endl;
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

        if (sprite->checkCollision(player, 15)) {
            cout << player->GetName() << " && " << sprite->GetName() << "충돌했습니다."  << endl;
        }
    }
}

void Bullets_dodge_Scene::bullet_position_create(int num, vec2& start, vec2& end)
{
    mt19937 gen1(mRandomDevice1());
    mt19937 gen2(mRandomDevice3());
    mt19937 gen3(mRandomDevice2());
    mt19937 gen4(mRandomDevice4());

    if (num > 300 && num <= 400)
    {
        uniform_int_distribution<int> random_1(front_vec.x, front_vec.z);
        uniform_int_distribution<int> random_2(front_vec.y, front_vec.w);
        start = vec2(random_1(gen1), random_2(gen2));
        uniform_int_distribution<int> random_3(back_vec.x, back_vec.z);
        uniform_int_distribution<int> random_4(back_vec.x, back_vec.z);
        end = vec2(random_3(gen3), random_4(gen4));
    }
    else if (num > 200 && num <= 300)
    {
        uniform_int_distribution<int> random_1(left_vec.x, left_vec.z);
        uniform_int_distribution<int> random_2(left_vec.y, left_vec.w);
        start = vec2(random_1(gen1), random_2(gen2));
        uniform_int_distribution<int> random_3(right_vec.x, right_vec.z);
        uniform_int_distribution<int> random_4(right_vec.x, right_vec.z);
        end = vec2(random_3(gen3), random_4(gen4));
    }
    else if (num > 100 && num <= 200)
    {
        uniform_int_distribution<int> random_1(back_vec.x, back_vec.z);
        uniform_int_distribution<int> random_2(back_vec.y, back_vec.w);
        start = vec2(random_1(gen1), random_2(gen2));
        uniform_int_distribution<int> random_3(front_vec.x, front_vec.z);
        uniform_int_distribution<int> random_4(front_vec.x, front_vec.z);
        end = vec2(random_3(gen3), random_4(gen4));
    }
    else
    {
        uniform_int_distribution<int> random_1(right_vec.x, right_vec.z);
        uniform_int_distribution<int> random_2(right_vec.y, right_vec.w);
        start = vec2(random_1(gen1), random_2(gen2));
        uniform_int_distribution<int> random_3(left_vec.x, left_vec.z);
        uniform_int_distribution<int> random_4(left_vec.x, left_vec.z);
        end = vec2(random_3(gen3), random_4(gen4));
    }
}

bool Bullets_dodge_Scene::isIntersecting2D(vec2 rayOrigin, vec2 rayDirection)
{
    float tMin = 0.0f;
    float tMax = std::numeric_limits<float>::max();

    for (int i = 0; i < 2; ++i) {
        float rayOriginCoord = (i == 0) ? rayOrigin.x : rayOrigin.y;
        float rayDirectionCoord = (i == 0) ? rayDirection.x : rayDirection.y;
        float boxMinCoord = (i == 0) ? boxMin.x : boxMin.y;
        float boxMaxCoord = (i == 0) ? boxMax.x : boxMax.y;

        if (std::abs(rayDirectionCoord) < std::numeric_limits<float>::epsilon())
        {
            if (rayOriginCoord < boxMinCoord || rayOriginCoord > boxMaxCoord)
            {
                return false;
            }
        }
        else 
        {
            float t1 = (boxMinCoord - rayOriginCoord) / rayDirectionCoord;
            float t2 = (boxMaxCoord - rayOriginCoord) / rayDirectionCoord;

            tMin = std::max(tMin, std::min(t1, t2));
            tMax = std::min(tMax, std::max(t1, t2));

            if (tMin > tMax)
            {
                return false;
            }
        }
    }
    return true;
}

void Bullets_dodge_Scene::bullet_create()
{
    mt19937 gen(mRandomDevice3());
    uniform_int_distribution<int> random_count(6, 16);
    int random_number = random_count(gen);
    for (int x = 0; x < random_number; x++)
    {
        if (mBulletMaxCount <= mBullet_count)
            return;

        mt19937 gen1(mRandomDevice2());
        uniform_int_distribution<int> random_speed(100, 1000);
        mt19937 gen2(mRandomDevice4());
        uniform_int_distribution<int> random_position(0, 399);

        vec2 start, end;
        while (true)
        {
            bullet_position_create(random_position(gen1), start, end);
            if (isIntersecting2D(start, end))
                break;
        }
        double speed = (static_cast<double>(random_speed(gen2)) / 10.0f);

        mpBullet[mBullet_count] = make_unique<dodge_bullet>(
            mpGame->GetTextureShader(),
            ".\\Image\\bullet1.png",
            start,
            end,
            speed);

        mSprites.push_back(mpBullet[mBullet_count]->GetSprite());
        mBullet_count++;
    }
}
