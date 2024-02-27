#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include "functions.h"

constexpr unsigned HEIGHT = 1000;
constexpr unsigned WIDTH  = 1000;

constexpr unsigned GRID_SZ_X = 51;
constexpr unsigned GRID_SZ_Y = 51;


using Rect = sf::RectangleShape;
using std::vector;
using Vec2f = sf::Vector2f;
using Vec2i = sf::Vector2i;

vector<vector<Rect>> grid(GRID_SZ_X, vector<Rect>(GRID_SZ_Y));


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "");

    // line_dda(20,20,25,20);
    // line_dda(20,10,20,40);
    // line_dda(0,0,25,33);
    
    // line_bresenham(20,20,30,10);
    // line_bresenham(0,0,40,40);
    // line_bresenham(0,0,40,10);
    // line_bresenham(50,50,30,10);
    // line_bresenham(20,20,5,25);
    // line_bresenham(0,50,50,0);
    line_bresenham(0,0,30,10);

    for (int i = 0; i < GRID_SZ_X; i++)
    {
        for (int j = 0; j < GRID_SZ_Y; j++)
        {
            float dx = (float)WIDTH/GRID_SZ_X;
            float dy = (float)HEIGHT/GRID_SZ_Y;

            grid[i][j].setSize({dx,dy});
            grid[i][j].setPosition({i*dx, j*dy});
            grid[i][j].setOutlineColor(sf::Color::Black);
            grid[i][j].setOutlineThickness(1);
        }
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (auto& line : grid)
            for (auto& rect : line)
                window.draw(rect);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        window.display();
    }

    return 0;
}


void fill_pixel(int x, int y)
{
    grid[x][y].setFillColor(sf::Color::Red);
}