#include <Raster.h>
#include <RasterPrimitives.h>


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


void Raster::setPixel(Vector2i pixel)
{
    setPixel(pixel.x, pixel.y);
}

void Raster::setPixel(int x, int y)
{
    m_raster.at(x).at(y).setFillColor(FILL_COLOR);
}

void Raster::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    for (const auto& line : m_raster)
        for (const auto& rect : line)
            target.draw(rect, states);
}



void Raster::drawLine(Vector2i r1, Vector2i r2)
{
    line_bresenham(*this, r1.x, r1.y, r2.x, r2.y);
    // line_dda(*this, r1.x, r1.y, r2.x, r2.y);
}


void Raster::drawCircle(Vector2i r0, unsigned R)
{
    circle_bresenham(*this, r0.x, r0.y, R);
    // circle_dda(*this, r0.x, r0.y, R);
}