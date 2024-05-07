#include "geometry.h"
#include <cmath>


int dot_product(Vec2i v1, Vec2i v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}
int cross_product(Vec2i v1, Vec2i v2)
{
    return v1.x*v2.y - v2.x*v1.y;
}

float length(Vec2i vec)
{
    return std::sqrt(vec.x*vec.x + vec.y*vec.y);
}


std::vector<Vec2i> outward_normals(const Polygon& polygon)
{
    int n = polygon.size()-1;
    float angle = 0;
    
    for (int i = 0; i < n; i++)
    {
        int j = i+1, k = (i+2)%n;
        Vec2i v1 = polygon[j] - polygon[i];
        Vec2i v2 = polygon[k] - polygon[j];

        angle += std::asin(cross_product(v1, v2) / length(v1) / length(v2));
    }

    bool f = angle < 0;
    std::vector<Vec2i> normals(n);

    for (int i = 0; i < n; i++)
    {
        Vec2i edge = polygon[i+1]-polygon[i];
        normals[i] = Vec2i{-edge.y, edge.x}*(f ? 1 : -1);
    }

    return normals;
}


std::optional<Vec2i> segment_line_intersection(Vec2i s1, Vec2i s2, Vec2i l1, Vec2i l2)
{
    Vec2i v = l1-l2, v1 = l1-s1, v2 = l1-s2;

    if (cross_product(v,v1)*cross_product(v,v2) > 0)
        return std::nullopt;

    float t = -(float)cross_product(l1-s1, s2-s1) / cross_product(l2-l1, s2-s1);
    float res_x = l1.x + (l2.x-l1.x)*t;
    float res_y = l1.y + (l2.y-l1.y)*t;
    return Vec2i{(int)std::round(res_x), (int)std::round(res_y)};
}