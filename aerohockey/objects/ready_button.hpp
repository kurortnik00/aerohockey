#pragma once

#include "paddle.hpp"

struct ReadyButton
{
    ReadyButton(sf::Vector2f position, sf::Vector2f size);
    bool isActivated();
    sf::RectangleShape shape();
    void update(Paddle & paddle);

private:
    sf::Vector2f position_, size_;
    sf::RectangleShape shape_;
    bool activated = false;
};
