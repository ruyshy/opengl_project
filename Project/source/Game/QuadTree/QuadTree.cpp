#include <pch.h>
#include <Game/QuadTree/QuadTree.h>

#include <OpenGL/Sprite/Sprite.h>
#include <OpenGL/Transform2D/Transform2D.h>


bool QuadTree::Rect::contains(shared_ptr<Sprite> sprite)
{
    return sprite->GetPosition().x >= x && sprite->GetPosition().x + sprite->GetScale().x <= x + width &&
        sprite->GetPosition().y >= y && sprite->GetPosition().y + sprite->GetScale().y <= y + height;
}

QuadTree::~QuadTree()
{
    for (auto& child : children) delete child;
}

void QuadTree::insert(shared_ptr<Sprite> sprite)
{
    if (!bounds.contains(sprite)) return;

    if (sprites.size() < MAX_CAPACITY || depth >= MAX_DEPTH) {
        sprites.push_back(sprite);
    }
    else {
        if (!children[0]) subdivide();

        for (auto& child : children) {
            child->insert(sprite);
        }
    }
}

void QuadTree::clear()
{
    sprites.clear();
    for (auto& child : children) {
        if (child) {
            child->clear();
            delete child;
            child = nullptr;
        }
    }
}

void QuadTree::retrieve(std::vector<shared_ptr<Sprite>>& returnSprites, shared_ptr<Sprite> sprite)
{
    if (!bounds.contains(sprite)) return;

    returnSprites.insert(returnSprites.end(), sprites.begin(), sprites.end());

    if (!children[0]) return;

    for (int i = 0; i < 4; i++) {
        if (children[i]->bounds.contains(sprite)) {
            children[i]->retrieve(returnSprites, sprite);
        }
    }
}

void QuadTree::subdivide()
{
    float halfWidth = bounds.width / 2.0;
    float halfHeight = bounds.height / 2.0;
    children[0] = new QuadTree(this, { bounds.x, bounds.y, halfWidth, halfHeight }, depth + 1);
    children[1] = new QuadTree(this, { bounds.x + halfWidth, bounds.y, halfWidth, halfHeight }, depth + 1);
    children[2] = new QuadTree(this, { bounds.x, bounds.y + halfHeight, halfWidth, halfHeight }, depth + 1);
    children[3] = new QuadTree(this, { bounds.x + halfWidth, bounds.y + halfHeight, halfWidth, halfHeight }, depth + 1);
}
