#include <cstdio>
#include <iostream>

//#include <SFML/Main.hpp>
#include <astra/astra.hpp>

//#include "objects/world.hpp"
//#include "states/state.hpp"
//#include "states/manager.hpp"


int main()
{
	astra::initialize();

	astra::StreamSet streamSet;
	astra::StreamReader reader = streamSet.create_reader();
	
	reader.stream<astra::DepthStream>().start();
	astra::Frame frame = reader.get_latest_frame();
	const auto depthFrame = frame.get<astra::DepthFrame>();

    /*World world(800.f, 600.f);
    StateManager manager(States::Type::Preparation, world);

    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    sf::Time update_time = sf::seconds(1.f / 60.f);

    while (world.mWindow.isOpen())
    {
        manager.processEvents();
        elapsed += clock.restart();

        while (elapsed > update_time)
        {
            manager.processEvents();
            manager.update(update_time.asSeconds());
            elapsed -= update_time;
        }

        manager.render();
    }*/

	astra::terminate();

	std::cout << "hit enter to exit program" << std::endl;
	std::cin.get();

    return EXIT_SUCCESS;
}
