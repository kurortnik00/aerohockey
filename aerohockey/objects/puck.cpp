#include <SFML/Graphics.hpp>
#include <iostream>

#include "puck.hpp"
#include "../util.hpp"

Puck::Puck (float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity)
    : radius_ (radius), color_ (color), position_ (position), velocity_ (velocity)
    , current (0), capacity (20), trace_ (capacity)
{    
    // Load puck texture and set up sprite
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
    trace_[current] = position_;
    current = (current + 1) % capacity;

    position_ += velocity_ * delta;
    sprite_.move(velocity_ * delta);
    //std::cout << "Update (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
    //std::cout << "Update collide (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
}

void Puck::render(sf::RenderWindow& window)
{
    float min_radius = 10.f, max_radius = radius_, current_radius = radius_;
    float step = (max_radius - min_radius) / capacity;
    for (int i = 0; i < capacity; i++)
    {
        current_radius -= step;

        int trace_index = current - i - 1;
        if (trace_index < 0)
        {
            trace_index = (trace_index + capacity) % capacity;
        }

        sf::CircleShape trace(current_radius);
        trace.setOrigin(current_radius, current_radius);
        trace.setPosition(trace_[trace_index]);
        trace.setFillColor(sf::Color(243, 240, 240, 64));

        window.draw(trace);
    }

    window.draw(sprite_);
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
