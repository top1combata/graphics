#include <cmath>
#include <Raster.h>


void Raster::line_dda(Vec2i p1, Vec2i p2, Color color)
{
    Vec2f delta(p2-p1);

    int m = std::max(std::abs(delta.x), std::abs(delta.y));

    float eps = 1.0/m;

    Vec2f p(p1);
    for (int i = 0; i <= m; i++)
    {
        setPixel((int)std::round(p.x), (int)std::round(p.y), color);
        p += eps*delta;     
    }
}


void Raster::line_bresenham(Vec2i p1, Vec2i p2, Color color)
{
    Vec2i delta = {std::abs(p2.x-p1.x), std::abs(p2.y-p1.y)};

    bool f = 1;

    if (delta.y > delta.x)
    {
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        std::swap(delta.x, delta.y);
        f = 0;
    }

    if (p1.x > p2.x)
        std::swap(p1, p2);

    int d = 2*delta.y - delta.x;
    int d1 = 2*delta.y, d2 = 2*delta.y - 2*delta.x;
    int dy = (p2.y > p1.y ? 1 : -1);

    for (auto [x,y] = p1; x <= p2.x; x++)
    {
        if (f) setPixel(x,y,color);
        else   setPixel(y,x,color);

        if (d < 0)
            d += d1;
        else
        {
            d += d2;
            y += dy;
        }
    }
}


void Raster::line_bresenham8(Vec2i p1, Vec2i p2, Color color)
{
    Vec2i delta = {std::abs(p2.x-p1.x), std::abs(p2.y-p1.y)};

    int dx = ((p2-p1).x > 0 ? 1 : -1);
    int dy = ((p2-p1).y > 0 ? 1 : -1);

    Vec2i p = p1;
    int d = delta.y-delta.x;
    while (p != p2)
    {
        setPixel(p, color);

        if (d < 0)
        {
            p.x += dx;
            d += 2*delta.y;       
        }
        else
        {
            p.y += dy;
            d -= 2*delta.x;
        }
    }
    setPixel(p2, color);
}


void Raster::circle_dda(Vec2i p0, int r, Color color)
{
    float eps = 0.5/r;

    float x = p0.x+r, y = p0.y;

    do
    {
        setPixel((int)std::round(x), (int)std::round(y), color);
        x += eps*(y-p0.y);
        y -= eps*(x-p0.x);
    }
    while (std::abs(x-p0.x-r) + std::abs(y-p0.y) > eps);
}


void Raster::symetry_fill(int x, int y, int x0, int y0, Color color)
{
    setPixel(x, y, color);
    setPixel(2*x0-x, y, color);
    setPixel(y-y0+x0, x-x0+y0, color);
    setPixel(x0+y0-y, x-x0+y0, color);
    setPixel(y-y0+x0, y0+x0-x, color);
    setPixel(x0+y0-y, y0+x0-x, color);
    setPixel(x, 2*y0-y, color);
    setPixel(2*x0-x,  2*y0-y, color);
}


void Raster::circle_bresenham(Vec2i p0, int r, Color color)
{
    int d = 3-2*r;
    auto [x0,y0] = p0;

    int end = std::round(x0 + r*std::sqrt(2)/2);
    for (int x = x0, y = y0+r; x <= end; x++)
    {
        symetry_fill(x, y, x0, y0, color);
        if (d < 0)
            d += 4*(x-x0)+6;
        else
        {
            d += 4*(x-y-x0+y0)+10;
            y--;
        }
    } 
}