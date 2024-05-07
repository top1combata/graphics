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
        int sign = cross_product(v1,v2) < 0 ? -1 : 1;

        angle += sign*std::acos(dot_product(v1, v2) / length(v1) / length(v2));
    }

    bool f = angle > 0;
    std::vector<Vec2i> normals(n);

    for (int i = 0; i < n; i++)
    {
        Vec2i edge = polygon[i+1]-polygon[i];
        normals[i] = Vec2i{-edge.y, edge.x}*(f ? -1 : 1);
    }

    return normals;
}


std::optional<Vec2i> line_line_intersection(pairVec2i line1, pairVec2i line2)
{
    auto [l1,l2] = line1;
    auto [l3,l4] = line2;
    if (cross_product(l4-l3, l2-l1) == 0)
        return std::nullopt;

    float t = (float)cross_product(l1-l3, l2-l1) / cross_product(l4-l3, l2-l1);
    float res_x = l3.x + (l4.x-l3.x)*t;
    float res_y = l3.y + (l4.y-l3.y)*t;
    return Vec2i{(int)std::round(res_x), (int)std::round(res_y)};
}


std::optional<Vec2i> segment_line_intersection(pairVec2i segment, pairVec2i line)
{
    auto [s1,s2] = segment;
    auto [l1,l2] = line;
    Vec2i v = l1-l2, v1 = l1-s1, v2 = l1-s2;

    if (cross_product(v,v1)*cross_product(v,v2) > 0)
        return std::nullopt;

    return line_line_intersection(segment, line);
}


std::optional<Vec2i> segment_segment_intersection(pairVec2i segment1, pairVec2i segment2)
{
    auto [s1,s2] = segment1;
    auto [s3,s4] = segment2;
    Vec2i s34 = s4-s3, s31 = s1-s3, s32 = s2-s3, s42 = s2-s4, s12 = s2-s1;

    if (cross_product(s34, s31)*cross_product(s34, s32) > 0 || cross_product(s12, s32)*cross_product(s12, s42) > 0)
        return std::nullopt;

    return line_line_intersection(segment1, segment2);
}


bool is_inside(Vec2i vert, const Polygon& polygon)
{
    constexpr float tol = 1e-3;
    
    float angle = 0;
    for (int i = 0; i < polygon.size()-1; i++)
    {
        Vec2i v1 = polygon[i]-vert, v2 = polygon[i+1]-vert;
        angle += std::asin(cross_product(v1,v2) / length(v1) / length(v2));
    }

    return std::abs(angle) > tol;
}