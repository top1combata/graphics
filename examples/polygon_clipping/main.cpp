#include <thread>
#include <SFML/Graphics.hpp>
#include <Raster.h>
#include "algorithms.h"

constexpr unsigned WIDTH  = 800;
constexpr unsigned HEIGHT = 800;

constexpr unsigned GRID_SZ_X = 121;
constexpr unsigned GRID_SZ_Y = 121;


int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "", sf::Style::Close);


    Raster raster(GRID_SZ_X, GRID_SZ_Y, WIDTH, HEIGHT);

    auto test_sutehrland_hodgman = [&raster]()
    {
        Raster::Polygon clip_polygon = {{31,31}, {50,20}, {81,31}, {71,81}, {41,81}, {31,31}};
        Raster::Polygon polygon = {{20,30},{50,10},{40,60},{20,50},{60,90},{55,70},{70,80},{75,105},{40,80},{60,110},{10,70},{15,50},{20,30}};
        
        raster.drawPolygon(clip_polygon);
        raster.drawPolygon(polygon, sf::Color::Blue);

        auto pols = clip_sutherland_hodgman(clip_polygon, polygon);

        for (auto poly : pols)
            raster.drawPolygon(poly, sf::Color::Green);
    };

    auto test_weiler_atherton = [&raster]()
    {
        // Raster::Polygon clip_polygon = {{30,90},{50,20},{80,80},{45,60},{30,90}};
        // Raster::Polygon polygon = {{30,30},{37,91},{84,20},{53,57},{30,30}};

        Raster::Polygon clip_polygon = {{20,90},{40,20},{70,80},{35,60},{20,90}};
        Raster::Polygon polygon = {{20,30},{50,10},{40,60},{20,50},{60,90},{55,70},{70,80},{75,105},{40,80},{60,110},{10,70},{15,50},{20,30}};
        

        raster.drawPolygon(clip_polygon);
        raster.drawPolygon(polygon, sf::Color::Blue);

        auto pols = clip_weiler_atherton(clip_polygon, polygon);

        for (auto poly : pols)
            raster.drawPolygon(poly, sf::Color::Green);
    };

    // test_sutehrland_hodgman();
    test_weiler_atherton();

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

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}