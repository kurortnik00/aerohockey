
#include <SFML/Graphics.hpp>
#include "puck.hpp"

Puck::Puck (float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity) 
    : radius_ (radius), color_ (color), position_ (position), velocity_ (velocity)
{
    shape_.setRadius(radius_);
    shape_.setFillColor(color_);
    shape_.setPosition(position_);
}


void Puck::update (int width, int height, float delta)
{
    shape_.move(velocity_ * delta);
    position_ = shape_.getPosition();
    walls_collide(width, height);
}


void Puck::reset(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}


sf::CircleShape Puck::shape()
{
    return shape_;
}


float Puck::radius()
{
    return radius_;
}


sf::Vector2f & Puck::position()
{
    return position_;
}


sf::Vector2f & Puck::velocity()
{
    return velocity_;
}


void Puck::walls_collide (int width, int height)
{
    if ((position_.y <= 0) || (position_.y >= height - 2 * radius_))
    {
        velocity_.y *= -1;
        if (position_.y <= 0)
        {
            position_.y = 0.1f;
        }
        else
        {
            position_.y = height - 2 * radius_ - 0.1f;
        }
    }
}
