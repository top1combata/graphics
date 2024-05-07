#include "algorithms.h"


std::vector<Polygon> clip_polygons_by_halfplane(const std::vector<Polygon>& polygons, Vec2i p1, Vec2i p2, Vec2i normal);

std::vector<Polygon> clip_sutherland_hodgman(const Polygon& clip_polygon, const Polygon& polygon)
{
    int n = clip_polygon.size()-1;

    // normals point outwards
    std::vector<Vec2i> normals = outward_normals(clip_polygon);

    std::vector<Polygon> res = {polygon};
    for (int i = 0; i < n; i++)
    {
        res = clip_polygons_by_halfplane(res, clip_polygon[i], clip_polygon[i+1], normals[i]);
    }
    return res;
}


std::vector<Polygon> clip_polygons_by_halfplane(const std::vector<Polygon>& polygons, Vec2i p1, Vec2i p2, Vec2i normal)
{
    std::vector<Polygon> res;

    // Ax + By + C = 0 line equation
    // (A,B) = normal
    int C = -dot_product(normal, p1);

    Polygon current;
    for (const Polygon& polygon : polygons)
    {
        int n = polygon.size();
        // searching for vertice outside the halfplane
        int start_idx = 0;
        for (; start_idx < n; start_idx++)
            if (dot_product(polygon[start_idx], normal) + C >= 0)
                break;

        // polygon fully inside the halfplane
        if (start_idx == n)
        {
            res.push_back(polygon);
            continue;
        }

        bool f = 0;
        for (int idx = (start_idx+1)%n, i = 0; i < n; idx = (idx+1)%n, i++)
        {
            Vec2i curr_vert = polygon[idx];
            Vec2i prev_vert = polygon[(idx+n-1)%n];
            auto intersection = segment_line_intersection({prev_vert, curr_vert}, {p1, p2});

            bool is_inside = dot_product(curr_vert, normal) + C < 0;
 
            // getting inside
            if (!f && is_inside)
            {
                current = {intersection.value()};
                current.push_back(curr_vert);
            }
            // still inside
            else if (f && is_inside)
            {
                current.push_back(curr_vert);
            }
            // going outside
            else if (f && !is_inside)
            {
                current.push_back(intersection.value());
                current.push_back(current.front());
                res.push_back(current);
                current = {};
            }
            

            f = is_inside;
        }
    }
    
    return res;
}