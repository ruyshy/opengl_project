#pragma once
#ifndef QUADTREE_H_
#define QUADTREE_H_

const int MAX_CAPACITY = 4;
const int MAX_DEPTH = 5;


class QuadTree 
{
public:
    struct Rect 
    {
        float x, y, width, height;
        Rect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

        bool contains(shared_ptr<Sprite> sprite);
    };

    QuadTree* parent;
    Rect bounds;
    vector<shared_ptr<Sprite>> sprites;
    QuadTree* children[4] = { nullptr };
    int depth;

    QuadTree(QuadTree* parent, Rect bounds, int depth) : parent(parent), bounds(bounds), depth(depth) {}
    ~QuadTree();

    void insert(shared_ptr<Sprite> sprite);
    void clear();

    void retrieve(std::vector<shared_ptr<Sprite>>& returnSprites, shared_ptr<Sprite> sprite);
    void subdivide();
private:
};


#endif // !QUADTREE_H_
