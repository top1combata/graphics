#pragma once

#include "geometry.h"

std::vector<Polygon> clip_sutherland_hodgman(const Polygon& clip_polygon, const Polygon& polygon);
std::vector<Polygon> clip_weiler_atherton(const Polygon& clip_polygon, const Polygon& polygon);