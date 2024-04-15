#include <thread>
#include <SFML/Graphics.hpp>
#include <Raster.h>

constexpr unsigned WIDTH  = 700;
constexpr unsigned HEIGHT = 700;

constexpr unsigned GRID_SZ_X = 141;
constexpr unsigned GRID_SZ_Y = 141;


int main()
{
    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "", sf::Style::Close);

    Raster raster(GRID_SZ_X, GRID_SZ_Y, WIDTH, HEIGHT);
    

    raster.drawCircle({50, 100}, 21, sf::Color::Green);
    raster.drawCircle({93, 100}, 21);
    raster.drawLine({50, 80}, {50, 21}, sf::Color::Black);
    raster.drawLine({93, 80}, {93, 21});
    raster.drawLine({50, 21}, {71, 10});
    raster.drawLine({93, 21}, {73, 10});
    raster.drawLine({72, 25}, {72, 10});


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