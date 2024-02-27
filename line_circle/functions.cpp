#include <algorithm>
#include <cmath>
#include <iostream>

void fill_pixel(int x, int y);



void draw_vertical(int x, int y0, int y1)
{
    int dy = (y1 > y0 ? 1 : -1);
    for (int y = y0; y != y1; y += dy)
        fill_pixel(x,y);
}

void line_dda(int x0, int y0, int x1, int y1)
{
    int delta_x = x1-x0;
    int delta_y = y1-y0;

    int dx = (delta_x < 0 ? -1 : 1);
    int dy = (delta_y < 0 ? -1 : 1);

    if (delta_x == 0)
    {
        draw_vertical(x0,y0,y1);
        return;
    }

    int m = std::max(delta_x, delta_y);

    float eps = 1.0/m;

    float x = x0, y = y0;
    for (int i = 0; i <= m; i++)
    {
        fill_pixel(std::round(x), std::round(y));
        x += eps*delta_x;
        y += eps*delta_y;       
    }
}


void line_bresenham(int x0, int y0, int x1, int y1)
{
    int delta_x = x1-x0;
    int delta_y = y1-y0;

    int dx = (delta_x < 0 ? -1 : 1);
    int dy = (delta_y < 0 ? -1 : 1);

    if (delta_x == 0)
    {
        draw_vertical(x0,y0,y1);
        return;
    }

    int x = x0, y = y0;
    /*
    int d = abs(delta_y)-abs(delta_x);

    while (x != x1 || y != y1)
    {
        fill_pixel(x,y);

        if (d < 0)
        {
            x += dx;
            d += 2*std::abs(delta_y);
        }
        else
        {
            d -= 2*std::abs(delta_x);
            y += dy;
        }
    }
    fill_pixel(x,y);
    */
   int d = 2*delta_y - delta_x;

    while (x != x1 && y != y1)
    {
        fill_pixel(x,y);

        if (d < 0)
        {
            d += 2*delta_y;
        }
        else
        {
            d += 2*(delta_y-delta_x);
            y++;
        }
        x++;
    }
}