#include <SFML/Graphics.hpp>
#include <iostream>

#include "puck.hpp"
#include "../util.hpp"

Puck::Puck (float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity)
    : radius_ (radius), color_ (color), position_ (position), velocity_ (velocity)
{
    std::string path = getcwd_string() + "/media/textures/puck-space.png";
    if (!texture_.loadFromFile(path))
    {
        std::cerr << "Failed to load texture: " << path << "\n";
    }
    else
    {
        sprite_.setTexture(texture_);
        sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);
        sprite_.setScale(2 * radius_ / texture_.getSize().x,
                         2 * radius_ / texture_.getSize().y);
    }

    sprite_.setPosition(position_);
}


void Puck::moveTo (sf::Vector2f position)
{
    position_ = position;
    sprite_.setPosition(position_);
}

void Puck::update (float delta)
{
    //std::cout << sprite_.getPosition().x << " " << sprite_.getPosition().y << "\n";
    //std::cout << delta << " " << velocity_.x * delta << " " << velocity_.y * delta << "\n";
    position_ += velocity_ * delta;
    sprite_.move(velocity_ * delta);
    //std::cout << "Update (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
    //std::cout << "Update collide (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
}


void Puck::reset(sf::Vector2f position, sf::Vector2f velocity)
{
    moveTo(position);
    velocity_ = velocity;
}


sf::Sprite & Puck::shape()
{
    return sprite_;
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


void Puck::walls_collide (float width, float height)
{
    if ((position_.y <= radius_) || (position_.y >= height - radius_))
    {
        // std::cout << "\nCollide with wall (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";

        velocity_.y *= -1;
        if (position_.y <= radius_)
        {
            position_.y = radius_ + 1.f;
        }
        else
        {
            position_.y = height - radius_ - 1.f;
        }
        sprite_.setPosition(position_);
        // std::cout << "After wall collide (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
    }
}
