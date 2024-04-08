#pragma once
#ifndef QUADTREE_H_
#define QUADTREE_H_

const int MAX_CAPACITY = 100;
const int MAX_DEPTH = 5;

class QuadTree
{
public:
    struct Rect 
    {
        float x, y, width, height;
        Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

        bool contains(const shared_ptr<Sprite>& sprite)
        {
            auto pos = sprite->GetPosition();
            auto scale = sprite->GetScale();
            return pos.x >= x && pos.x + scale.x <= x + width &&
                pos.y >= y && pos.y + scale.y <= y + height;
        }
    };

    QuadTree* parent;
    Rect bounds;
    vector<shared_ptr<Sprite>> sprites;
    QuadTree* children[4] = { nullptr };
    int depth;

    QuadTree(QuadTree* parent, Rect bounds, int depth) : parent(parent), bounds(bounds), depth(depth) {}
    ~QuadTree();

    void insert(const shared_ptr<Sprite>& sprite);
    void clear();
    void retrieve(std::vector<shared_ptr<Sprite>>& returnSprites, const shared_ptr<Sprite>& sprite);
    void subdivide();

private:
    int getIndex(const vec2& position);
};

#endif // !QUADTREE_H_
