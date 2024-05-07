#include "algorithms.h"


struct TraversalVertex
{
    enum VertexType
    {   
        NONE,
        ENTERING,
        EXITING
    };

    Vec2i vertex;
    VertexType type;
};

using TraversalList = std::vector<TraversalVertex>;


// getting traversal list in clockwise order for traverse polygon, intersecting with another polygon
TraversalList get_traversal(const Polygon& traverse_polygon, const Polygon& polygon);

std::vector<Polygon> clip_weiler_atherton(const Polygon& clip_polygon, const Polygon& polygon)
{
    TraversalList clipping_list = get_traversal(clip_polygon, polygon);
    TraversalList clipped_lsit  = get_traversal(polygon, clip_polygon);



    return {};
}


TraversalList get_traversal(const Polygon& traverse_polygon, const Polygon& polygon)
{

}