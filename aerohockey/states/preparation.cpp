#include <iostream>
#include <SFML/Graphics.hpp>

#include "state.hpp"

void StatePreparation::processEvents()
{
    world.processEvents();
}

void StatePreparation::update(const float delta)
{
    State::update(delta);

    world.left.update(world.width_, world.height_, delta);
    world.right.update(world.width_, world.height_, delta);
    world.left_ready.update(world.left);
    world.right_ready.update(world.right);
}

void StatePreparation::render()
{
    world.mWindow.clear();

    world.mWindow.draw(world.background);
    world.mWindow.draw(world.left.shape());
    world.mWindow.draw(world.right.shape());
    world.mWindow.draw(world.left_ready.shape());
    world.mWindow.draw(world.right_ready.shape());

    world.mWindow.display();
}

States::Type StatePreparation::switchTo()
{
    if (world.left_ready.isActivated() && world.right_ready.isActivated())
    {
        return States::Type::Game;
    }
    return States::Type::Preparation;
}
