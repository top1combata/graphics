#include <cmath>
#include <algorithm>
#include <stack>
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


void Raster::polygon_active_edges(const Polygon& polygon, sf::Color color)
{

}


void Raster::polygon_filling(const Polygon& polygon, sf::Color color)
{
    int y_max = std::max_element(polygon.begin(), polygon.end(), [](Vector2i v1, Vector2i v2) {return v1.y < v2.y;})->y;

    Vector2i v1, v2, v;

    for (int i = 0; i < polygon.size()-1; i++)
    {
        drawLine(polygon[i], polygon[i+1], color);
        if (polygon[i].y == y_max)
        {
            v = polygon[i];
            v1 = polygon[i+1]-polygon[i];
            v2 = polygon[i == 0 ? polygon.size()-2 : i-1]-polygon[i];
        }
    }

    Vector2i b = v1+v2;
    float magn = sqrt(b.x*b.x + b.y*b.y);

    Vector2i start_pixel = {v.x + 3.0*b.x/magn, v.y + 3.0*b.y/magn};

    std::stack<Vector2i> stack;
    stack.push(start_pixel);

    std::vector<Vector2i> dirs = {{1,0},{0,1},{-1,0},{0,-1}};

    while (!stack.empty())
    {
        Vector2i pixel = stack.top();
        stack.pop();

        setPixel(pixel, color);

        for (Vector2i dir : dirs)
            if (getPixel(pixel+dir) != color)
                stack.push(pixel+dir);
    }
}