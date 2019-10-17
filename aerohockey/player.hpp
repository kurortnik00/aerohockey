#pragma once

#include <SFML/Graphics.hpp>

struct Player
{
public:
    Player(float radius, sf::Color color, sf::Vector2f position, float velocity);
    void update();
    sf::CircleShape shape();
    float radius();
    sf::Vector2f & position();
    sf::Vector2f & velocity();
	unsigned score();
	void scored();

private:
    sf::CircleShape shape_;
    float radius_;
    sf::Color color_;
	unsigned score_;
    sf::Vector2f position_;
    sf::Vector2f velocity_;
};