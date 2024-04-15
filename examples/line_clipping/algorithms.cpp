#include <cmath>
#include "algorithms.h"


enum CODES
{
    TOP = 8,
    BOTTOM = 4,
    LEFT = 1,
    RIGHT = 2
};

int get_code(Rect rect, Vec2i p)
{
    int res = 0;
    if (p.x < rect.xmin)
        res |= LEFT;
    if (p.x > rect.xmax)
        res |= RIGHT;
    if (p.y < rect.ymin)
        res |= TOP;
    if (p.y > rect.ymax)
        res |= BOTTOM;

    return res;
}


std::optional<Line> clip_cohen_sutherland(Rect rect, Line line)
{
    auto [p1,p2] = line;
    int c1 = get_code(rect, p1);
    int c2 = get_code(rect, p2);

    while (c1|c2)
    {
        if (c1&c2)
            return std::nullopt;

        if (c1 == 0)
        {
            std::swap(c1,c2);
            std::swap(p1, p2);
        }

        if (c1 & TOP)
            p1 = {(int)std::round(p1.x + float(p2.x - p1.x)*(rect.ymin - p1.y)/(p2.y - p1.y)), rect.ymin};

        else if (c1 & BOTTOM)
            p1 = {(int)std::round(p1.x + float(p2.x - p1.x)*(rect.ymax - p1.y)/(p2.y - p1.y)), rect.ymax};

        else if (c1 & RIGHT)
            p1 = {rect.xmax, (int)std::round(p1.y + float(p2.y - p1.y)*(rect.xmax - p1.x)/(p2.x - p1.x))};

        else if (c1 & LEFT)
            p1 = {rect.xmin, (int)std::round(p1.y + float(p2.y - p1.y)*(rect.xmin - p1.x)/(p2.x - p1.x))};

        c1 = get_code(rect, p1);
        c2 = get_code(rect, p2);
    }

    return Line{p1,p2};   
}


std::optional<Line> clip_liang_barsky(Rect rect, Line line)
{
    auto [p1,p2] = line;
    float t1 = 0, t2 = 1;
    
    if (p2.x - p1.x > 0)
    {
        t1 = std::max(t1, float(rect.xmin - p1.x)/(p2.x - p1.x));
        t2 = std::min(t2, float(rect.xmax - p1.x)/(p2.x - p1.x));
    }
    else if (p2.x - p1.x < 0)
    {
        t1 = std::max(t1, float(rect.xmax - p1.x)/(p2.x - p1.x));
        t2 = std::min(t2, float(rect.xmin - p1.x)/(p2.x - p1.x));
    }
    else if (p1.x < rect.xmin || p1.x > rect.xmax)
        return std::nullopt;

    if (p2.y - p1.y > 0)
    {
        t1 = std::max(t1, float(rect.ymin - p1.y)/(p2.y - p1.y));
        t2 = std::min(t2, float(rect.ymax - p1.y)/(p2.y - p1.y));
    }
    else if (p2.y - p1.y < 0)
    {
        t1 = std::max(t1, float(rect.ymax - p1.y)/(p2.y - p1.y));
        t2 = std::min(t2, float(rect.ymin - p1.y)/(p2.y - p1.y));
    }
    else if (p1.y < rect.ymin || p1.y > rect.ymax)
        return std::nullopt;

    if (t1 > t2)
        return std::nullopt;
    
    Vec2i r1 = {(int)std::round(p1.x + t1*(p2.x-p1.x)), (int)std::round(p1.y + t1*(p2.y-p1.y))};
    Vec2i r2 = {(int)std::round(p1.x + t2*(p2.x-p1.x)), (int)std::round(p1.y + t2*(p2.y-p1.y))};
    return Line{r1,r2};
}


int dot_product(Vec2i v1, Vec2i v2)
{
    return v1.x*v2.x + v1.y*v2.y;
}
int cross_product(Vec2i v1, Vec2i v2)
{
    return v1.x*v2.y - v2.x*v1.y;
}

std::optional<Line> clip_cyrus_beck(const Polygon& polygon, Line line)
{
    int n = polygon.size()-1;
    // normal point outwards
    std::vector<Vec2i> normals(n);

    bool f = cross_product(polygon[1]-polygon[0], polygon[2]-polygon[1]) < 0;
    for (int i = 0; i < n; i++)
        normals[i] = Vec2i{polygon[i].y-polygon[i+1].y, polygon[i+1].x-polygon[i].x}*(f ? 1 : -1);

    auto [p1,p2] = line;

    float t1 = 0, t2 = 1;
    for (int i = 0; i < n; i++)
    {
        int prod = dot_product(p2-p1, normals[i]);
        if (prod)
        {
            float t = dot_product(polygon[i]-p1, normals[i]) / (float)prod;
            if (prod > 0)
                t2 = std::min(t2, t);
            else 
                t1 = std::max(t1, t);
        }
        else if (dot_product(p1-polygon[i], normals[i]) > 0)
            return std::nullopt;
    }

    if (t1 > t2)
        return std::nullopt;
    
    Vec2i r1 = {(int)std::round(p1.x + t1*(p2.x-p1.x)), (int)std::round(p1.y + t1*(p2.y-p1.y))};
    Vec2i r2 = {(int)std::round(p1.x + t2*(p2.x-p1.x)), (int)std::round(p1.y + t2*(p2.y-p1.y))};
    return Line{r1,r2};
}

Rect::operator Polygon() const
{
    return {{xmin,ymin}, {xmin,ymax}, {xmax,ymax}, {xmax,ymin}, {xmin, ymin}};
}