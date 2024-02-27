#include <algorithm>
#include <cmath>

void fill_pixel(int x, int y);


void line_dda(int x1, int y1, int x2, int y2)
{
    float delta_x = x2-x1;
    float delta_y = y2-y1;

    int m = std::max(delta_x, delta_y);

    float eps = 1.0/m;

    float x = x1, y = y1;
    for (int i = 0; i <= m; i++)
    {
        fill_pixel(std::round(x), std::round(y));
        x += eps*delta_x;
        y += eps*delta_y;       
    }
}


void line_bresenham(int x1, int y1, int x2, int y2)
{
    int delta_x = std::abs(x2-x1);
    int delta_y = std::abs(y2-y1);

    bool f = 1;

    if (delta_y > delta_x)
    {
        std::swap(x1,y1);
        std::swap(x2,y2);
        std::swap(delta_x, delta_y);
        f = 0;
    }

    if (x1 > x2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }

    int d = 2*delta_y - delta_x;
    int d1 = 2*delta_y, d2 = 2*delta_y - 2*delta_x;
    int dy = (y2 > y1 ? 1 : -1);

    for (int x = x1, y = y1; x <= x2; x++)
    {
        if (f) fill_pixel(x,y);
        else   fill_pixel(y,x);

        if (d < 0)
            d += d1;
        else
        {
            d += d2;
            y += dy;
        }
    }
}



void circle_dda(int x0, int y0, int r)
{
    float eps = 0.5/r;

    float x = x0+r, y = y0;

    do
    {
        fill_pixel(std::round(x), std::round(y));
        x += eps*(y-y0);
        y -= eps*(x-x0);
    }
    while (std::abs(x-x0-r) + std::abs(y-y0) > eps);
}


inline void symetry_fill(int x, int y, int x0, int y0)
{
    fill_pixel(x, y);
    fill_pixel(2*x0-x, y);
    fill_pixel(y-y0+x0, x-x0+y0);
    fill_pixel(x0+y0-y, x-x0+y0);
    fill_pixel(y-y0+x0, y0+x0-x);
    fill_pixel(x0+y0-y, y0+x0-x);
    fill_pixel(x, 2*y0-y);
    fill_pixel(2*x0-x,  2*y0-y);
}

void circle_bresenham(int x0, int y0, int r)
{
    int d = 3-2*r;

    int end = std::round(x0 + r*std::sqrt(2)/2);
    for (int x = x0, y = y0+r; x <= end; x++)
    {
        symetry_fill(x,y,x0,y0);
        if (d < 0)
            d += 4*(x-x0)+6;
        else
        {
            d += 4*(x-y-x0+y0)+10;
            y--;
        }
    } 
}