#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


using sf::Vector2i;


struct Raster : public sf::Drawable
{
public:

    Raster(unsigned sz_x, unsigned sz_y, unsigned window_width, unsigned window_height);
    
    void setPixel(Vector2i pixel, sf::Color color = DEFAULT_FILL_COLOR);
    void setPixel(int x, int y, sf::Color color = DEFAULT_FILL_COLOR);
    sf::Color getPixel(Vector2i pixel);
    sf::Color getPixel(int x, int y);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    // drawing primitives
    void drawLine(Vector2i r1, Vector2i r2, sf::Color color = DEFAULT_FILL_COLOR);

    void drawCircle(Vector2i r0, unsigned r, sf::Color color = DEFAULT_FILL_COLOR);

    using Polygon = std::vector<Vector2i>;
    void drawPolygon(const Polygon& polygon, sf::Color color = DEFAULT_FILL_COLOR);

private:

    std::vector<std::vector<sf::RectangleShape>> m_raster;
    unsigned m_window_height;
    unsigned m_window_width;

    static const sf::Color DEFAULT_FILL_COLOR;

    // lines
    void line_dda(int x1, int y1, int x2, int y2, sf::Color color);
    void line_bresenham(int x1, int y1, int x2, int y2, sf::Color color);

    // circles
    void circle_dda(int x0, int y0, int r, sf::Color color);
    void circle_bresenham(int x0, int y0, int r, sf::Color color);

    // polygons
    void polygon_scanline(const Polygon& polygon, sf::Color color);
    void polygon_active_edges(const Polygon& polygon, sf::Color color);
    void polygon_filling(const Polygon& polygon, sf::Color color);
    void polygon_line_filling(const Polygon& polygon, sf::Color color);
};