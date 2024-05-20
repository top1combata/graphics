#pragma once

#include <vector>
#include <string>
#include <Raster.h>

using Vec2f = Raster::Vec2f;
using Vec2i = Raster::Vec2i;

struct Face
{
    int v1,v2,v3;
};

struct Wavefront
{
    std::vector<Vec2f> vertices;
    std::vector<Face> faces;
};

Wavefront parse(const std::string& path);