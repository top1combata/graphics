#include "algorithms.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

struct TraversalVertex
{
    enum class VertexType
    {   
        NONE,
        ENTERING,
        EXITING
    };

    Vec2i vertex;
    VertexType type;
};

using TraversalList = std::vector<TraversalVertex>;

namespace std
{
    template<>
    struct hash<Vec2i>
    {
        size_t operator()(Vec2i vec) const
        {
            std::hash<int> h;
            return h(vec.x) ^ h(vec.y);
        }
    };
}


// getting traversal list in clockwise order for traverse polygon, intersecting with another polygon
TraversalList get_traversal(Polygon traverse_polygon, const Polygon& polygon);

std::vector<Polygon> clip_weiler_atherton(const Polygon& clip_polygon, const Polygon& polygon)
{
    using enum TraversalVertex::VertexType;

    TraversalList clipping_list = get_traversal(clip_polygon, polygon);
    TraversalList clipped_list  = get_traversal(polygon, clip_polygon);

    int n = clipping_list.size(), m = clipped_list.size();

    // mapping for fast searching corresponding vertex
    std::unordered_map<Vec2i, int> clipping_mapping;
    for (int i = 0; i < n; i++)
    {
        auto [vertex, type] = clipping_list[i];

        if (type != NONE)
            clipping_mapping[vertex] = i;
    }

    std::unordered_map<Vec2i, int> clipped_mapping;
    for (int i = 0; i < m; i++)
    {
        auto [vertex, type] = clipped_list[i];

        if (type != NONE)
            clipped_mapping[vertex] = i;
    }

    std::vector<Polygon> res;
    std::unordered_set<Vec2i> visited;
    for (int idx = 0; idx < m; idx++)
    {
        auto [test_vertex, type] = clipped_list[idx];
        if (type == ENTERING && !visited.count(test_vertex))
        {
            Polygon tmp = {test_vertex};
            int i = (idx+1)%m, j;
            int di = 1, dj;
            bool f = 1;
            Vec2i vertex = clipped_list[i].vertex;

            while (vertex != test_vertex)
            {
                tmp.push_back(vertex);
                visited.insert(vertex);

                if (f && clipped_list[i].type != NONE)
                {
                    // swap to clipping
                    f = 0;
                    j = clipping_mapping[vertex];
                    dj = clipping_list[j].type == ENTERING ? 1 : -1;
                }
                else if (!f && clipping_list[j].type != NONE)
                {
                    // swap to clipped
                    f = 1;
                    i = clipped_mapping[vertex];
                    di = clipped_list[i].type == ENTERING ? 1 : -1;
                }

                if (f)
                {
                    i = (i+di+m)%m;
                    vertex = clipped_list[i].vertex;
                }
                else
                {
                    j = (j+dj+n)%n;
                    vertex = clipping_list[j].vertex;
                }
            }
            tmp.push_back(vertex);
            res.push_back(tmp);
        }
    }
    // clipped polygon is inside
    if (res.size() == 0 && is_inside(polygon[0], clip_polygon))
        res = {polygon};

    return res;
}


TraversalList get_traversal(Polygon traverse_polygon, const Polygon& polygon)
{
    using enum TraversalVertex::VertexType;

    std::vector<Vec2i> travers_normals = outward_normals(traverse_polygon);
    std::vector<Vec2i> normals  = outward_normals(polygon);

    // making polygon in clockwise order
    if (cross_product(traverse_polygon[1] - traverse_polygon[0], travers_normals[0]) < 0)
        std::reverse(traverse_polygon.begin(), traverse_polygon.end());

    int n = traverse_polygon.size()-1;
    int m = polygon.size()-1;

    TraversalList res;
    // iterating through edges
    for (int i = 0; i < n; i++)
    {
        Vec2i next_vertex = traverse_polygon[i+1];
        Vec2i curr_vertex = traverse_polygon[i];
        Vec2i edge = next_vertex - curr_vertex;

        res.push_back({curr_vertex, NONE});

        // list of intersection point and edge index
        std::vector<std::pair<Vec2i, int>> intersections;
        for (int j = 0; j < m; j++)
        {
            auto intersection = segment_segment_intersection({curr_vertex, next_vertex}, {polygon[j], polygon[j+1]});
            if (intersection.has_value())
                intersections.push_back({intersection.value(), j});
        }
        
        auto cmp = [curr_vertex](std::pair<Vec2i, int> p1,  std::pair<Vec2i, int> p2)
        {
            return length(p1.first - curr_vertex) < length(p2.first - curr_vertex);
        };
        std::sort(intersections.begin(), intersections.end(), cmp);

        for (auto [vertex, edge_idx] : intersections)
        {
            bool is_entering = dot_product(normals[edge_idx], edge) < 0;
            res.push_back({vertex, (is_entering ? ENTERING : EXITING)});
        }
    }
    return res;
}