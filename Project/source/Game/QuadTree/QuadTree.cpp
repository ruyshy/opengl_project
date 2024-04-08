#include <pch.h>
#include <Game/QuadTree/QuadTree.h>

#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Transform2D/Transform2D.h>


QuadTree::~QuadTree()
{
    for (auto& child : children)
        delete child;
}

void QuadTree::insert(const shared_ptr<Sprite>& sprite)
{
    if (!bounds.contains(sprite)) return;
    if (sprites.size() < MAX_CAPACITY || depth >= MAX_DEPTH)
    {
        sprites.push_back(sprite);
        return;
    }
    if (!children[0]) 
        subdivide();

    bool inserted = false;
    for (auto& child : children)
    {
        if (child->bounds.contains(sprite)) 
        {
            child->insert(sprite);
            inserted = true;
            break;
        }
    }
    if (!inserted) sprites.push_back(sprite);
}

void QuadTree::clear()
{
    sprites.clear();
    for (auto& child : children) 
    {
        if (child) 
        {
            child->clear();
            delete child;
            child = nullptr;
        }
    }
}

void QuadTree::retrieve(std::vector<shared_ptr<Sprite>>& returnSprites, const shared_ptr<Sprite>& sprite)
{
    if (!bounds.contains(sprite)) return;
    returnSprites.insert(returnSprites.end(), sprites.begin(), sprites.end());
    if (!children[0]) return;

    int index = getIndex(sprite->GetPosition());
    if (index != -1 && children[index]) 
        children[index]->retrieve(returnSprites, sprite);
    else 
        for (int i = 0; i < 4; i++)
            if (children[i])
                children[i]->retrieve(returnSprites, sprite);

}

void QuadTree::subdivide() {
    float halfWidth = bounds.width / 2.0;
    float halfHeight = bounds.height / 2.0;

    children[0] = new QuadTree(this, { bounds.x, bounds.y, halfWidth, halfHeight }, depth + 1);
    children[1] = new QuadTree(this, { bounds.x + halfWidth, bounds.y, halfWidth, halfHeight }, depth + 1);
    children[2] = new QuadTree(this, { bounds.x, bounds.y + halfHeight, halfWidth, halfHeight }, depth + 1);
    children[3] = new QuadTree(this, { bounds.x + halfWidth, bounds.y + halfHeight, halfWidth, halfHeight }, depth + 1);

}

int QuadTree::getIndex(const vec2& position) 
{
    int index = -1;
    double horizontalMidpoint = bounds.x + (bounds.width / 2.0);
    double verticalMidpoint = bounds.y + (bounds.height / 2.0);
    bool topQuadrant = (position.y < verticalMidpoint);
    bool bottomQuadrant = (position.y > verticalMidpoint);

    if (position.x < horizontalMidpoint) {
        if (topQuadrant) index = 1;
        else if (bottomQuadrant) index = 2;
    }
    else if (position.x > horizontalMidpoint) {
        if (topQuadrant) index = 0;
        else if (bottomQuadrant) index = 3;
    }

    return index;
}