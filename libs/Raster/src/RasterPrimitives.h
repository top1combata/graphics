#pragma once

#include <Raster.h>


void line_dda(Raster& grid, int x1, int y1, int x2, int y2);
void line_bresenham(Raster& grid, int x1, int y1, int x2, int y2);

void circle_dda(Raster& grid, int x0, int y0, int r);
void circle_bresenham(Raster& grid, int x0, int y0, int r);