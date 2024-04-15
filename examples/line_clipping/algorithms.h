#include <Raster.h>
#include <optional>

using Vec2i = Raster::Vec2i;
using Vec2f = Raster::Vec2f;
using Polygon = Raster::Polygon;

struct Line
{
    Vec2i p1,p2;
};

struct Rect
{
    int xmin, ymin, xmax, ymax;
    operator Polygon() const;
};

std::optional<Line> clip_cohen_sutherland(Rect rect, Line line);
std::optional<Line> clip_liang_barsky(Rect rect, Line line);
std::optional<Line> clip_cyrus_beck(const Polygon& polygon, Line line);