#include <thread>
#include <SFML/Graphics.hpp>
#include <Raster.h>

constexpr unsigned WIDTH  = 700;
constexpr unsigned HEIGHT = 700;

constexpr unsigned GRID_SZ_X = 201;
constexpr unsigned GRID_SZ_Y = 201;


int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "", sf::Style::Close);

    Raster raster(GRID_SZ_X, GRID_SZ_Y, WIDTH, HEIGHT);
    

    // Raster::Polygon polygon = {{30,10},{10,30},{30,50},{50,30},{30,10}};
    // Raster::Polygon polygon = {{10,10},{10,30},{30,30},{30,10},{10,10}};
    // Raster::Polygon polygon = {{20,20},{120,40},{130,10},{120,80},{40,120},{10,70},{20,20}};
    // Raster::Polygon polygon = {{50,20},{100,20},{130,80},{20,80},{50,20}};
    Raster::Polygon polygon = {{20,20},{20,140},{60,100},{60,60},{20,20}};
    // Raster::Polygon polygon = {{50,50},{80,30},{70,80},{50,70},{90,110},{85,90},{100,100},{105,125},{70,100},{90,130},{40,90},{45,70},{50,50}};
    // Raster::Polygon polygon = {{40,40},{60,20},{80,40},{100,20},{100,100},{20,100},{20,20},{40,40}};

    raster.drawPolygon(polygon);


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