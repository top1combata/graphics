#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


using sf::Vector2i;


struct Raster : public sf::Drawable
{
private:

    std::vector<std::vector<sf::RectangleShape>> m_raster;
    unsigned m_window_height;
    unsigned m_window_width;

    const sf::Color FILL_COLOR = sf::Color::Red;


public:

    Raster(unsigned sz_x, unsigned sz_y, unsigned window_width, unsigned window_height);
    
    void setPixel(Vector2i pixel);
    void setPixel(int x, int y);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void drawLine(Vector2i r1, Vector2i r2);

    void drawCircle(Vector2i r0, unsigned r);
};