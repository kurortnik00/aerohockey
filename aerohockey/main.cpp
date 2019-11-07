#include <iostream>
#include <SFML/Main.hpp>

#include "objects/world.hpp"
#include "states/state.hpp"
#include "states/manager.hpp"


int main()
{
    World world(800.f, 600.f);
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
    }

    return EXIT_SUCCESS;
}
