#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

struct Raster : public sf::Drawable
{
public:

    Raster(unsigned sz_x, unsigned sz_y, unsigned window_width, unsigned window_height);

    using Vec2i = sf::Vector2i;
    using Vec2f = sf::Vector2f;
    using Polygon = std::vector<Vec2i>;
    using Color = sf::Color;
    
    void setPixel(Vec2i pixel, Color color = DEFAULT_FILL_COLOR);
    void setPixel(int x, int y, Color color = DEFAULT_FILL_COLOR);
    Color getPixel(Vec2i pixel);
    Color getPixel(int x, int y);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    // drawing primitives
    void drawLine(Vec2i r1, Vec2i r2, Color color = DEFAULT_FILL_COLOR);

    void drawCircle(Vec2i r0, unsigned r, Color color = DEFAULT_FILL_COLOR);

    void drawPolygon(const Polygon& polygon, Color color = DEFAULT_FILL_COLOR);

private:

    std::vector<std::vector<sf::RectangleShape>> m_raster;
    unsigned m_window_height;
    unsigned m_window_width;

    static const Color DEFAULT_FILL_COLOR;

    // lines
    void line_dda(Vec2i p1, Vec2i p2, Color color);
    void line_bresenham(Vec2i p1, Vec2i p2, Color color);
    void line_bresenham8(Vec2i p1, Vec2i p2, Color color);

    // circles
    void circle_dda(Vec2i p0, int r, Color color);
    void circle_bresenham(Vec2i p0, int r, Color color);
    // routine for bresenham circle
    void symetry_fill(int x, int y, int x0, int y0, Color color);

    // polygons
    void polygon_scanline(const Polygon& polygon, Color color);
    void polygon_active_edges(const Polygon& polygon, Color color);
    void polygon_filling(const Polygon& polygon, Color color);
    void polygon_line_filling(const Polygon& polygon, Color color);
    // for filling
    Vec2i find_start_pixel(const Polygon& polygon, Color color);
};