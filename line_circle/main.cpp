#include <thread>
#include "../grid.h"
#include "functions.h"

constexpr unsigned WIDTH  = 700;
constexpr unsigned HEIGHT = 700;

constexpr unsigned GRID_SZ_X = 141;
constexpr unsigned GRID_SZ_Y = 141;


Grid grid(GRID_SZ_X, GRID_SZ_Y, WIDTH, HEIGHT);


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "", sf::Style::Close);
    
    // line_bresenham(20,20,30,10);
    // line_bresenham(0,0,40,40);
    // line_bresenham(0,0,40,10);
    // line_bresenham(50,50,30,10);
    // line_bresenham(25,5,20,20);
    // line_bresenham(0,50,50,0);

    circle_bresenham(50, 100, 21);
    circle_bresenham(93, 100, 21);
    line_bresenham(50, 80, 50, 21);
    line_bresenham(93, 80, 93, 21);
    line_bresenham(50, 21, 71, 10);
    line_bresenham(93, 21, 73, 10);
    line_bresenham(72, 25, 72, 10);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.draw(grid);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}


void fill_pixel(int x, int y)
{
    grid.SetPixel(x,y);
}