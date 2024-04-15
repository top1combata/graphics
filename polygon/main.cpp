#include <thread>
#include <SFML/Graphics.hpp>
#include <Raster.h>

constexpr unsigned WIDTH  = 1000;
constexpr unsigned HEIGHT = 1000;

constexpr unsigned GRID_SZ_X = 251;
constexpr unsigned GRID_SZ_Y = 251;


int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "", sf::Style::Close);

    Raster raster(GRID_SZ_X, GRID_SZ_Y, WIDTH, HEIGHT);
    

    // Raster::Polygon polygon = {{30,10},{10,30},{30,50},{50,30},{30,10}};
    // Raster::Polygon polygon = {{10,10},{10,30},{30,30},{30,10},{10,10}};
    
    Raster::Polygon polygon1 = {{20,30},{50,10},{40,60},{20,50},{60,90},{55,70},{70,80},{75,105},{40,80},{60,110},{10,70},{15,50},{20,30}};
    Raster::Polygon polygon2 = {{80,20},{90,10},{100,20},{110,10},{110,50},{70,50},{70,10},{80,20}};
    Raster::Polygon polygon3 = {{140,20},{240,40},{250,10},{240,80},{160,120},{130,7},{140,20}};
    Raster::Polygon polygon4 = {{20,120},{20,240},{60,200},{60,160},{20,120}};
    Raster::Polygon polygon5 = {{100,120},{150,120},{180,180},{70,180},{100,120}};

    raster.drawPolygon(polygon1);
    raster.drawPolygon(polygon2);
    raster.drawPolygon(polygon3);
    raster.drawPolygon(polygon4);
    raster.drawPolygon(polygon5);

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