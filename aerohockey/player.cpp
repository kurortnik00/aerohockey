#include <SFML/Graphics.hpp>
//#include <Kinect.h>

#include "player.hpp"


Player::Player (float radius, sf::Color color, sf::Vector2f position, float velocity)
      : radius_ (radius), color_ (color), position_ (position), velocity_ (sf::Vector2f(0.0, 0.0))
{
    shape_.setRadius(radius_);
    shape_.setFillColor(color_);
    shape_.setPosition(position_);
}


void Player::update ()
{
    shape_.move(velocity_);
    position_ = shape_.getPosition();
}


sf::CircleShape Player::shape()
{
    return shape_;
}


float Player::radius()
{
    return radius_;
}


sf::Vector2f & Player::position()
{
    return position_;
}


sf::Vector2f & Player::velocity()
{
    return velocity_;
}

unsigned Player::score()
{
	return score_;
}

void Player::scored()
{
	score_++;
}
