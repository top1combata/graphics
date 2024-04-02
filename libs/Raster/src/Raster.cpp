#include <Raster.h>


const sf::Color Raster::DEFAULT_FILL_COLOR = sf::Color::Red;


Raster::Raster(unsigned sz_x, unsigned sz_y, unsigned window_width, unsigned window_height) : m_raster(sz_x, std::vector<sf::RectangleShape>(sz_y, sf::RectangleShape({(float)window_width/sz_x, (float)window_height/sz_y}))),
        m_window_height(window_height),
        m_window_width(window_width)
{
    for (int x = 0; x < sz_x; x++)
    {
        for (int y = 0; y < sz_y; y++)
        {
            m_raster[x][y].setOutlineColor({0,0,0,80});
            m_raster[x][y].setOutlineThickness(1);
            m_raster[x][y].setPosition({x*(float)window_width/sz_x, y*(float)window_height/sz_y});
        }
    }
}


void Raster::setPixel(Vector2i pixel, sf::Color color)
{
    setPixel(pixel.x, pixel.y, color);
}

void Raster::setPixel(int x, int y, sf::Color color)
{
    m_raster.at(x).at(y).setFillColor(color);
}

sf::Color Raster::getPixel(Vector2i pixel)
{
    return getPixel(pixel.x, pixel.y);
}

sf::Color Raster::getPixel(int x, int y)
{
    return m_raster.at(x).at(y).getFillColor();
}


void Raster::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    for (const auto& line : m_raster)
        for (const auto& rect : line)
            target.draw(rect, states);
}



void Raster::drawLine(Vector2i r1, Vector2i r2, sf::Color color)
{
    line_bresenham(r1.x, r1.y, r2.x, r2.y, color);
    // line_dda(r1.x, r1.y, r2.x, r2.y, color);
}


void Raster::drawCircle(Vector2i r0, unsigned R, sf::Color color)
{
    circle_bresenham(r0.x, r0.y, R, color);
    // circle_dda(r0.x, r0.y, R, color);
}


void Raster::drawPolygon(const Polygon& polygon, sf::Color color)
{
    // polygon_scanline(polygon, color);
    // polygon_filling(polygon, color);
    // polygon_active_edges(polygon, color);
    polygon_line_filling(polygon, color);
}