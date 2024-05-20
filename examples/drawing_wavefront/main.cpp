#include <thread>
#include <SFML/Graphics.hpp>
#include <Raster.h>
#include <iostream>
#include "parse.h"

constexpr unsigned WIDTH  = 1000;
constexpr unsigned HEIGHT = 1000;

constexpr unsigned GRID_SZ_X = 500;
constexpr unsigned GRID_SZ_Y = 500;


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "argument must be a path\n";
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "", sf::Style::Close);

    Raster raster(GRID_SZ_X, GRID_SZ_Y, WIDTH, HEIGHT);

    
    auto [vertices, faces] = parse(argv[1]);
    // transforming vertices
    for (Vec2f& vertex : vertices)
    {
        vertex.x = (vertex.x+1)/2 * (GRID_SZ_X-1);
        vertex.y = (-vertex.y+1)/2 * (GRID_SZ_Y-1);
    }

    //drawing
    for (auto [i1,i2,i3] : faces)
    {
        Vec2i v1 = (Vec2i)vertices[i1-1];
        Vec2i v2 = (Vec2i)vertices[i2-1];
        Vec2i v3 = (Vec2i)vertices[i3-1];
        raster.drawLine(v1,v2);
        raster.drawLine(v1,v3);
        raster.drawLine(v2,v3);
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.draw(raster);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}