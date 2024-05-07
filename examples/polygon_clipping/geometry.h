#include <Raster.h>
#include <optional>

using Vec2i = Raster::Vec2i;
using Vec2f = Raster::Vec2f;
using Polygon = Raster::Polygon;

int dot_product(Vec2i v1, Vec2i v2);
int cross_product(Vec2i v1, Vec2i v2);
float length(Vec2i);

std::optional<Vec2i> segment_line_intersection(Vec2i s1, Vec2i s2, Vec2i l1, Vec2i l2);
std::vector<Vec2i> outward_normals(const Polygon& polygon);
