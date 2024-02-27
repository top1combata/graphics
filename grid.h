#include <SFML/Graphics.hpp>


struct Grid : public sf::Drawable
{
private:

    std::vector<std::vector<sf::RectangleShape>> m_grid;
    unsigned m_window_height;
    unsigned m_window_width;

public:

    Grid(unsigned sz_x, unsigned sz_y, unsigned window_width, unsigned window_height) 
        : m_grid(sz_x, std::vector<sf::RectangleShape>(sz_y, sf::RectangleShape({(float)window_width/sz_x, (float)window_height/sz_y}))),
          m_window_height(window_height),
          m_window_width(window_width)
    {
        for (int x = 0; x < sz_x; x++)
        {
            for (int y = 0; y < sz_y; y++)
            {
                m_grid[x][y].setOutlineColor({0,0,0,80});
                m_grid[x][y].setOutlineThickness(1);
                m_grid[x][y].setPosition(x*(float)window_width/sz_x, y*(float)window_height/sz_y);
            }
        }
    }
    
    void SetPixel(unsigned x, unsigned y)
    {
        m_grid.at(x).at(y).setFillColor(sf::Color::Red);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const auto& line : m_grid)
            for (const auto& rect : line)
                target.draw(rect, states);
    }
};