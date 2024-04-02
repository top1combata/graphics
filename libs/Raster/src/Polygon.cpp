#include <cmath>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
#include <Raster.h>



void Raster::polygon_scanline(const Polygon& polygon, sf::Color color)
{
    int y_min = std::min_element(polygon.begin(), polygon.end(), [](Vector2i v1, Vector2i v2) {return v1.y < v2.y;})->y;
    int y_max = std::max_element(polygon.begin(), polygon.end(), [](Vector2i v1, Vector2i v2) {return v1.y < v2.y;})->y;

    
    std::vector<std::vector<int>> intervals(y_max - y_min + 1);

    for (int y = y_min; y <= y_max; y++)
    {
        int idx = y-y_min;
        for (int i = 0; i < polygon.size()-1; i++)
        {
            auto [x1,y1] = polygon[i];
            auto [x2,y2] = polygon[i+1];

            if (y1 == y2)
                continue;

            if (std::min(y1,y2) <= y && y <= std::max(y1,y2))
            {
                int x = std::round(x1 + float(y-y1)/(y2-y1)*(x2-x1));
                
                // JOPA)))))
                bool f = intervals[idx].size() &&  (y == y1 && (y1 - polygon[i-1].y)*(y2 - y1) >= 0 || y == y2 && y == polygon[0].y && (polygon[1].y - y2)*(y2 - y1) >= 0);
                if (!f)
                    intervals[idx].push_back(x);
            }
        }
        
        std::sort(intervals[idx].begin(), intervals[idx].end());
    }

    // filling
    for (int y = y_min; y <= y_max; y++)
    {
        int idx = y - y_min;
        for (int i = 0; i < intervals[idx].size()-1; i += 2)
            for (int x = intervals[idx][i]; x <= intervals[idx][i+1]; x++)
                setPixel(x,y,color);
    }
}


struct Edge
{
    Vector2i v1,v2;
};


void Raster::polygon_active_edges(const Polygon& polygon, sf::Color color)
{
    int y_min = std::min_element(polygon.begin(), polygon.end(), [](Vector2i v1, Vector2i v2) {return v1.y < v2.y;})->y;
    int y_max = std::max_element(polygon.begin(), polygon.end(), [](Vector2i v1, Vector2i v2) {return v1.y < v2.y;})->y;

    std::list<Edge> active_edges;

    std::list<Edge> unused_edges;
    for (int i = 0; i < polygon.size()-1; i++)
        if (polygon[i].y != polygon[i+1].y) 
            unused_edges.push_back({polygon[i], polygon[i+1]});


    for (int y = y_min; y < y_max; y++)
    {
        // std::cout << y << std::endl;
        auto it = unused_edges.begin();
        while (it != unused_edges.end())
        {
            auto prev = it++;
            if (std::min(prev->v1.y, prev->v2.y) == y)
            {
                active_edges.push_back(*prev);
                unused_edges.erase(prev);                
            }
        }

        it = active_edges.begin();
        while (it != active_edges.end())
        {
            auto prev = it++;
            if (std::max(prev->v1.y, prev->v2.y) <= y)
                active_edges.erase(prev);
        }

        std::vector<int> intersections;
        for (const Edge& edge : active_edges)
        {
            int x = std::round(edge.v1.x + float(y-edge.v1.y)/(edge.v2.y-edge.v1.y)*(edge.v2.x-edge.v1.x));
            intersections.push_back(x);
        }

        std::sort(intersections.begin(), intersections.end());

        for (int i = 0; i < intersections.size()-1; i += 2)
        {
            for (int x = intersections[i]; x <= intersections[i+1]; x++)
                setPixel(x,y,color);            
        }   
    }
}


Vector2i find_start_pixel(const Raster&, const Raster::Polygon&, sf::Color color);

void Raster::polygon_filling(const Polygon& polygon, sf::Color color)
{

    for (int i = 0; i < polygon.size()-1; i++)
        drawLine(polygon[i], polygon[i+1], color);


    std::queue<Vector2i> queue;
    queue.push(find_start_pixel(*this, polygon, color));
    
    std::vector<Vector2i> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

    while (queue.size())
    {
        Vector2i pixel = queue.front();
        queue.pop();
        if (getPixel(pixel) == color)
            continue;

        setPixel(pixel, color);

        for (Vector2i dir : dirs)
            if (getPixel(pixel+dir) != color)
                queue.push(pixel+dir);
    }
}


void Raster::polygon_line_filling(const Polygon& polygon, sf::Color color)
{
    for (int i = 0; i < polygon.size()-1; i++)
        drawLine(polygon[i], polygon[i+1], color);

    std::stack<Vector2i> stack;
    stack.push(find_start_pixel(*this, polygon, color));

    while (stack.size())
    {
        Vector2i pixel = stack.top();
        stack.pop();

        if (getPixel(pixel) == color)
            continue;

        int y = pixel.y;

        int x_min = pixel.x;
        while (getPixel({x_min-1, y}) != color)
            x_min--;

        int x_max = pixel.x;
        while (getPixel({x_max+1, y}) != color)
            x_max++;          

        for (int x = x_min; x <= x_max; x++)
        {
            setPixel(x,y,color);

            if (getPixel({x,y-1}) != color)
                stack.push({x,y-1});

            if (getPixel({x,y+1}) != color)
                stack.push({x,y+1});
        }
    }
}


Vector2i find_start_pixel(const Raster& raster, const Raster::Polygon& polygon, sf::Color color)
{
    int y_max = std::max_element(polygon.begin(), polygon.end(), [](Vector2i v1, Vector2i v2) {return v1.y < v2.y;})->y;

    Vector2i v, v1, v2;

    for (int i = 0; i < polygon.size()-1; i++)
    {
        if (polygon[i].y == y_max)
        {
            v = polygon[i];
            v1 = polygon[i+1];
            v2 = polygon[i == 0 ? polygon.size()-2 : i-1];
        }
    }


    if (v1.y == v.y)
        return {(v1.x+v.x)/2, v.y-1};

    if (v2.y == v.y)
        return {(v2.x+v.x)/2, v.y-1};

    for (int y = y_max; y; y--)
    {
        int x1 = std::round(v1.x + float(y-v1.y)/(v.y-v1.y)*(v.x-v1.x));
        int x2 = std::round(v2.x + float(y-v2.y)/(v.y-v2.y)*(v.x-v2.x));

        if (std::abs(x1-x2) > 2)
            return {(x1+x2)/2, y};
    }
    return {-1,-1};
}