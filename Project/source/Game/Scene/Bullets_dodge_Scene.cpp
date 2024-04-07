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
    
    front_vec = vec4(rect.x - 5, rect.y - 5, rect.x, rect.y);
    back_vec = vec4(rect.width, rect.height, rect.width + 5, rect.height + 5);
    right_vec = vec4(rect.x - 5, rect.y, rect.x, rect.height + 5);
    left_vec = vec4(rect.width, rect.y, rect.width + 5, rect.height);

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
        if (mpBullet[x]->EndGoal())
        {
            if (mpBullet[x]->GetState())
                continue;

            mpBullet[x]->SetState(true);
            mBulletEndIndexQueue.push(mBullet_count);
        }
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

int Bullets_dodge_Scene::randomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen); // 'gen'은 'std::mt19937' 객체

}

float Bullets_dodge_Scene::randomFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}


void Bullets_dodge_Scene::bullet_position_create(int num, vec2& start, vec2& end)
{
    if (num > 30 && num <= 40)
    {
        cout << "num : " << num << endl;
        start = vec2(randomFloat(front_vec.x, front_vec.z), randomFloat(front_vec.y, front_vec.w));
        end = vec2(randomFloat(back_vec.x, back_vec.z), randomFloat(back_vec.y, back_vec.w));
    }
    else if (num > 20 && num <= 30)
    {
        cout << "num : " << num << endl;
        start = vec2(randomFloat(left_vec.x, left_vec.z), randomFloat(left_vec.y, left_vec.w));
        end = vec2(randomFloat(right_vec.x, right_vec.z), randomFloat(right_vec.y, right_vec.w));
    }
    else if (num > 10 && num <= 20)
    {
        cout << "num : " << num << endl;
        start = vec2(randomFloat(back_vec.x, back_vec.z), randomFloat(back_vec.y, back_vec.w));
        end = vec2(randomFloat(front_vec.x, front_vec.z), randomFloat(front_vec.y, front_vec.w));
    }
    else if( num > 0 && num <= 10)
    {
        cout << "num : " << num << endl;
        start = vec2(randomFloat(right_vec.x, right_vec.z), randomFloat(right_vec.y, right_vec.w));
        end = vec2(randomFloat(left_vec.x, left_vec.z), randomFloat(left_vec.y, left_vec.w));
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
    uniform_int_distribution<int> random_count(16, 24);
    int random_number = random_count(gen);
    for (int x = 0; x < random_number; x++)
    {
        if (mBulletMaxCount <= mBullet_count)
            return;

        vec2 start, end;
        bullet_position_create(randomInt(0, 40), start, end);
        double speed = (static_cast<double>(randomInt(600, 2500)) / 10.0f);
        cout << "start.x : " << start.x << " start.y : " << start.y << endl;
        cout << "end.x : " << end.x << " end.y : " << end.y << endl;

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
