#include <pch.h>

QuadtreeNode::QuadtreeNode(float x, float y, float width, float height, int depth, int maxDepth, int maxObjects)
    : bounds(x, y, width, height), depth(depth), maxDepth(maxDepth), maxObjects(maxObjects)
{

}

void QuadtreeNode::insert(const Rect& obj)
{
    if (depth == maxDepth) 
    {
        objects.push_back(obj);
        return;
    }

    if (!children.empty()) 
    {
        for (auto& child : children)
        {
            if (child.bounds.intersects(obj)) 
            {
                child.insert(obj);
                return;
            }
        }
    }

    if (objects.size() >= maxObjects) 
    {
        if (children.empty())
        {
            split();
        }
        for (auto& child : children)
        {
            if (child.bounds.intersects(obj)) 
            {
                child.insert(obj);
                return;
            }
        }
    }

    objects.push_back(obj);
}

std::vector<QuadtreeNode::Rect> QuadtreeNode::queryRange(const Rect& range) const
{
    std::vector<Rect> found;

    if (!bounds.intersects(range)) 
    {
        return found;
    }

    for (const auto& obj : objects) 
    {
        if (obj.intersects(range)) {
            found.push_back(obj);
        }
    }

    if (!children.empty()) 
    {
        for (const auto& child : children) 
        {
            auto childFound = child.queryRange(range);
            found.insert(found.end(), childFound.begin(), childFound.end());
        }
    }

    return found;
}

void QuadtreeNode::split()
{
    float x = bounds.x, y = bounds.y, w = bounds.width / 2, h = bounds.height / 2;

    children.emplace_back(x, y, w, h, depth + 1, maxDepth, maxObjects);
    children.emplace_back(x + w, y, w, h, depth + 1, maxDepth, maxObjects);
    children.emplace_back(x, y + h, w, h, depth + 1, maxDepth, maxObjects);
    children.emplace_back(x + w, y + h, w, h, depth + 1, maxDepth, maxObjects);
}
