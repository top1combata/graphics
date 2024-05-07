#pragma once

#include <Raster.h>
#include <optional>

using Vec2i = Raster::Vec2i;
using Vec2f = Raster::Vec2f;
using Polygon = Raster::Polygon;

int dot_product(Vec2i v1, Vec2i v2);
int cross_product(Vec2i v1, Vec2i v2);
float length(Vec2i);

using pairVec2i = std::pair<Vec2i, Vec2i>;

std::optional<Vec2i> line_line_intersection(pairVec2i line1, pairVec2i line2);
std::optional<Vec2i> segment_line_intersection(pairVec2i segment, pairVec2i line);
std::optional<Vec2i> segment_segment_intersection(pairVec2i segment1, pairVec2i segment2);

std::vector<Vec2i> outward_normals(const Polygon& polygon);

bool is_inside(Vec2i vert, const Polygon& polygon);