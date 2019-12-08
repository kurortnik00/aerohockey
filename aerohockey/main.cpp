#include <SFML/Main.hpp>

#include <iostream>

#include "easylogging/easylogging++.h"
#include "objects/world.hpp"
#include "states/state.hpp"
#include "states/manager.hpp"

INITIALIZE_EASYLOGGINGPP

int main()
{
    sf::Time update_time = sf::seconds(1.f / 120.f);

	// Initialize Kinect tracking
	bool kinectControl = false;
    BodyTracker kinect;
	kinect.Run();

    World world(800.f, 600.f, update_time.asSeconds(), kinect, kinectControl);
    StateManager manager(States::Type::Preparation, world, kinect, kinectControl);

    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
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

		sf::sleep(sf::microseconds(1));
    }

    return EXIT_SUCCESS;
}
