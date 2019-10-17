#pragma once

#include <SFML/Graphics.hpp>

struct Puck
{
public:
    Puck(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity);
    void update(int width, int height, float delta);
	void reset(sf::Vector2f position);
    sf::CircleShape shape();
    float radius();
    sf::Vector2f & position();
    sf::Vector2f & velocity();    
    
private:
    void walls_collide (int width, int height);

    sf::CircleShape shape_;
    float radius_;
    sf::Color color_;
    sf::Vector2f position_;
    sf::Vector2f velocity_;
};