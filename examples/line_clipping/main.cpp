#include <thread>
#include <SFML/Graphics.hpp>
#include <Raster.h>
#include "algorithms.h"

constexpr unsigned WIDTH  = 800;
constexpr unsigned HEIGHT = 800;

constexpr unsigned GRID_SZ_X = 101;
constexpr unsigned GRID_SZ_Y = 101;

#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "", sf::Style::Close);

    Raster raster(GRID_SZ_X, GRID_SZ_Y, WIDTH, HEIGHT);

    Rect rect{20,20,70,70};
    // Polygon rect = {{20,20},{50,20},{70,60},{70,80},{40,90},{10,70},{20,20}};

    std::vector<Line> lines = {
        {{40,30},{65,15}},
        {{10,10},{17,60}},
        {{10,25},{10,50}},  
        {{90,60},{50,90}},
        {{20,10},{50,10}},
        {{50,40},{80,40}},
        {{30,15},{30,80}},
        {{45,75},{80,60}},
        {{40,40},{50,65}}
    };

    for (Line line : lines)
        raster.drawLine(line.p1, line.p2, sf::Color::Black);

    raster.drawPolygon(rect);

    for (Line line : lines)
    {
        auto clipped = clip_liang_barsky(rect, line);
        if (clipped.has_value())
            raster.drawLine(clipped.value().p1, clipped.value().p2, sf::Color::Green);
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

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}