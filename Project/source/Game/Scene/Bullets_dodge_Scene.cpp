#include <pch.h>
#include <Game/Scene/Bullets_dodge_Scene.h>
#include <Game/Game.h>
#include <Game/Object/Player/Player.h>
#include <OpenGL/Quad/Quad.h>
#include <utill/TimeMeasure.h>

#include <rc/font_resource.h>

void Bullets_dodge_Scene::initializeScene()
{
    QuadTree::Rect rect(0, 0, *mpGame->GetWindow()->GetWidth(), *mpGame->GetWindow()->GetHeight());
    mpQuadTree = make_shared<QuadTree>(nullptr, rect, 0);
    
    mpGameStartText = make_unique<TextRendering>(IDB_FONT_ARIAL,
        mpGame->GetWindow()->getOrthoProjectionMatrix(),
        mpGame->GetCamera()->GetViewMatrix(),
        vec2(0,0),
        0.4f);

    boxMin = vec2(rect.x, rect.y);
    boxMax = vec2(rect.width, rect.height);

    mBulletMinX = mBulletMinY = -20;
    mBulletMaxX = rect.width + 20;
    mBulletMaxY = rect.height + 20;

    mpBackGround = make_shared<Sprite>(mpGame->GetTextureShader(), ".\\Image\\back_ground.png");
    mpBackGround->SetPosition(0,0);
    mpBackGround->SetScale(*mpGame->GetWindow()->GetWidth(), *mpGame->GetWindow()->GetHeight());
    mpScore = make_unique<Score_dodge>(mpGame);

	mpPlayer = make_shared<Player>(mpGame->GetTextureShader(), ".\\Image\\Player.png");
    mpPlayer->GetSprite()->SetScale(vec2(50, 50));
    vec2 half_size = vec2(mpPlayer->GetSprite()->GetScale().x / 2, mpPlayer->GetSprite()->GetScale().y / 2);
    mpPlayer->GetSprite()->SetPosition(vec2(*mpGame->GetWindow()->GetWidth() / 2, *mpGame->GetWindow()->GetHeight() / 2) - half_size);
    mpPlayer->GetSprite()->SetDepth(0.1);
    mpPlayer->SetSpeed(250.0f);

    for (int x = 0; x < mBulletMaxCount; x++)
    {
        mpBullet[x] = make_unique<dodge_bullet>(
            mpGame->GetTextureShader(),
            ".\\Image\\bullet1.png",
            vec2(-20,-20),
            vec2(-20,-20),
            0);
    }

    mSprites = vector<shared_ptr<Sprite>>();

    mScore = 0;
    mGameStart = false;
    mGameEnd = false;
}

void Bullets_dodge_Scene::renderScene()
{
    mpBackGround->Draw();

    for (int x = 0; x < mBullet_count; x++)
        mpBullet[x]->Draw();
	mpPlayer->Draw();

    if (!mGameStart)
    {
        mpGameStartText->RenderText(mStartTextContexts,
            (*mpGame->GetWindow()->GetWidth() / 2) - 200,
            (*mpGame->GetWindow()->GetHeight() / 2),
            vec3(1, 1, 1));
    }
    if (mGameEnd)
    {
        mpGameStartText->RenderText(mEndTextContexts,
            (*mpGame->GetWindow()->GetWidth() / 2) - 220,
            (*mpGame->GetWindow()->GetHeight() / 2),
            vec3(1, 1, 1));
    }

    mpScore->Draw(mScore);
}

void Bullets_dodge_Scene::updateScene()
{
    if (mGameEnd)
    {
        if (mpGame->GetWindow()->keyPressed(GLFW_KEY_ENTER) ||
            mpGame->GetWindow()->keyPressed(GLFW_KEY_SPACE))
        {
            initializeScene();
            mGameStart = true;
            return;
        }
        return;
    }
    if (!mGameStart)
    {
        if(mpGame->GetWindow()->keyPressed(GLFW_KEY_ENTER) ||
            mpGame->GetWindow()->keyPressed(GLFW_KEY_SPACE))
            mGameStart = true;
        return;
    }

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

    for (int x = 0; x < mBulletMaxCount; x++) 
    {
        if (mpBullet[x]->EndGoal())
        {
            if (mpBullet[x]->GetState())
                continue;
            mpBullet[x]->SetState(true);
            mBulletEndIndexQueue.push(x);
        }
        else
            mpBullet[x]->Movement(mpGame->GetWindow()->getTimeDelta());
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    updateQuadTree(mpQuadTree, mSprites);
    checkPlayerBulletCollisions(mpQuadTree, mpPlayer);
}

void Bullets_dodge_Scene::releaseScene()
{

}

void Bullets_dodge_Scene::updateQuadTree(shared_ptr<QuadTree> quadTree, const vector<shared_ptr<Sprite>>& bullets)
{
    quadTree->clear();

    for (auto& bullet : bullets) 
    {
        if (bullet->hasMoved()) 
        {
            quadTree->insert(bullet);
            bullet->update();
        }
    }
}

void Bullets_dodge_Scene::checkPlayerBulletCollisions(shared_ptr<QuadTree> quadTree, shared_ptr<Player> player)
{
    vector<shared_ptr<Sprite>> candidateBullets;
    quadTree->retrieve(candidateBullets, player->GetSprite());
    for (auto& bullet : candidateBullets) 
    {
        if (player->GetSprite()->checkCollision(bullet, 10))
        {
            mGameEnd = true;
            break;
        }
    }

}

int Bullets_dodge_Scene::randomInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);

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
        start = vec2(mBulletMinX, randomFloat(mBulletMinY, mBulletMaxY));
        end = vec2(mBulletMaxX, randomFloat(mBulletMinY, mBulletMaxY));
    }
    else if (num > 20 && num <= 30)
    {
        start = vec2(randomFloat(mBulletMinX, mBulletMaxX), mBulletMinY);
        end = vec2(randomFloat(mBulletMinX, mBulletMaxX), mBulletMaxY);
    }
    else if (num > 10 && num <= 20)
    {
        start = vec2(mBulletMaxX, randomFloat(mBulletMinY, mBulletMaxY));
        end = vec2(mBulletMinX, randomFloat(mBulletMinY,mBulletMaxY));
    }
    else if( num > 0 && num <= 10)
    {
        start = vec2(randomFloat(mBulletMinX, mBulletMaxX), mBulletMaxY);
        end = vec2(randomFloat(mBulletMinX, mBulletMaxX), mBulletMinY);
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
    uniform_int_distribution<int> random_count(24, 40);
    int random_number = random_count(gen);
    if (mBulletMaxCount > (mBullet_count + random_number))
    {
        for (int x = 0; x < random_number; x++)
        {
            if (mBulletMaxCount <= mBullet_count)
                return;

            vec2 start, end;
            bullet_position_create(randomInt(0, 40), start, end);
            double speed = (static_cast<double>(randomInt(600, 2500)) / 10.0f);

            mpBullet[mBullet_count]->reload(start, end, speed);
            mSprites.push_back(mpBullet[mBullet_count]->GetSprite());
            mBullet_count++;
        }
        return;
    }
    for (int x = 0; x < mBulletEndIndexQueue.size(); x++)
    {
        int pop_index = mBulletEndIndexQueue.front();
        mBulletEndIndexQueue.pop();

        vec2 start, end;
        bullet_position_create(randomInt(0, 40), start, end);
        double speed = (static_cast<double>(randomInt(600, 2500)) / 10.0f);

        mpBullet[pop_index]->reload(start, end, speed);
        mpBullet[pop_index]->SetState(false);
    }
}
