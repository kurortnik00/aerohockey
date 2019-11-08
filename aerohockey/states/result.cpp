#include <iostream>

#include "state.hpp"

void StateResult::render()
{
    world.board.render(world.mWindow);
}

States::Type StateResult::switchTo()
{
    if (timeElapsed > 5.f)
    {
        return States::Type::Preparation;
    }
    return States::Type::Result;
}
