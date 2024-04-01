
#ifndef QUADTREENODE_H_
#define QUADTREENODE_H_

#endif // !QUADTREENODE_H_


class QuadtreeNode {
public:
    struct Rect {
        float x, y, width, height;

        Rect(float x, float y, float width, float height)
            : x(x), y(y), width(width), height(height) {}

        bool intersects(const Rect& other) const {
            return !(x + width < other.x || x > other.x + other.width ||
                y + height < other.y || y > other.y + other.height);
        }
    };

    QuadtreeNode(float x, float y, float width, float height, int depth = 0, int maxDepth = 4, int maxObjects = 10);
    void insert(const Rect& obj);

    std::vector<Rect> queryRange(const Rect& range) const;

private:
    Rect bounds;
    std::vector<Rect> objects;
    std::vector<QuadtreeNode> children;
    int depth, maxDepth, maxObjects;

    void split();
};