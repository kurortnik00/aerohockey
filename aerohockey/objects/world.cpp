#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "world.hpp"
#include "../util.hpp"

using namespace std;


World::World(float width, float height)
    : width_(width), height_(height), score_changed(false), paused(false)
    , mWindow(sf::VideoMode(width, height), "Aerohockey", sf::Style::None)
    , puck (height / 20, sf::Color::White, sf::Vector2f(width / 2, height / 2), sf::Vector2f(150.f, 200.f))
    , left (height / 20, sf::Color(204, 0, 0), sf::Vector2f(100, height / 2), 250.f, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D)
    , right (height / 20, sf::Color(0, 102, 0), sf::Vector2f(width - 100, height / 2), 250.f, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right)
    , board (&left, &right, 0.5)
    , left_ready (sf::Vector2f(200, height / 2), sf::Vector2f(width / 8, width / 8))
    , right_ready (sf::Vector2f(width - 200, height / 2), sf::Vector2f(width / 8, width / 8))
{
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(2.f, height_ - 60.f));
    left_border.setFillColor(sf::Color(204, 0, 0));

    right_border.setPosition(798.f, 0.f);
    right_border.setSize(sf::Vector2f(2.f, height_ - 60.f));
    right_border.setFillColor(sf::Color(0, 102, 0));

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(800.f, 2.f));
    left_border.setFillColor(sf::Color::White);
}


void World::processEvents()
{
    left.handleInput();
    right.handleInput();
}


void World::update(const float delta)
{
    left.update(width_, height_, delta);
    right.update(width_, height_, delta);
    puck.update(width_, height_, delta);
    collide_objects(left, puck, width_, height_, delta);
    collide_objects(right, puck, width_, height_, delta);
    puck.walls_collide(width_, height_);

    score_changed = goal_scored();
    board.update(delta, score_changed);
}


void World::collide_objects(Paddle & first, Puck & second, int width, int height, float delta)
{
    float r1 = first.radius();
    float r2 = second.radius();
    float threshold = (r1 + r2) * (r1 + r2);
    sf::Vector2f x1 = first.position(), x2 = second.position();

    float dist = dist2(x1, x2);
    if (dist2(x1, x2) <= threshold)
    {
        sf::Vector2f v1 = first.velocity(), v2 = second.velocity();
        float rewind_time = 0.f;
        if (dist < threshold)
        {
            sf::Vector2f dv = v1 - v2;
            rewind_time = (r1 + r2 - sqrt(dist)) / sqrt(len2(dv));
            second.moveTo(x2 - rewind_time * v2);
        }

        sf::Vector2f x1 = first.position(), x2 = second.position();
        first.velocity() = v1 - (x1 - x2) * dot(v1 - v2, x1 - x2) / len2(x1 - x2);
        second.velocity() = v2 - (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);

        first.update(width, height, rewind_time);
        second.update(width, height, rewind_time);
    }
}


void World::collide_objects(Puck * first, Puck * second, int width, int height)
{
    float r1 = first->radius();
    float r2 = second->radius();
    float threshold = (r1 + r2) * (r1 + r2);
    sf::Vector2f x1 = first->position(), x2 = second->position();

    float dist = dist2(x1, x2);
    if (dist <= threshold)
    {
        sf::Vector2f v1 = first->velocity(), v2 = second->velocity();

        float rewind_time = 0.f;
        if (dist < threshold)
        {
            sf::Vector2f dv = v1 - v2;
            rewind_time = (r1 + r2 - sqrt(dist)) / sqrt(len2(dv));
            std::cout << r1 + r2 << " " << sqrt(dist) << " " << dv.x << " " << dv.y << " " << rewind_time << "\n";
            first->moveTo(x1 - rewind_time * v1);
            second->moveTo(x2 - rewind_time * v2);
        }

        sf::Vector2f x1 = first->position(), x2 = second->position();
        first->velocity() = v1 - (x1 - x2) * dot(v1 - v2, x1 - x2) / len2(x1 - x2);
        second->velocity() = v2 - (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);

        first->update(width, height, rewind_time);
        second->update(width, height, rewind_time);
    }
}

bool World::goal_scored()
{
    sf::Vector2f velocity;

    if ((puck.position().x < 0) || (puck.position().x > width_))
    {
        if (puck.position().x < 0)
        {
            right.scored();
            velocity = sf::Vector2f(-150.f, 200.f);
        }
        else
        {
            left.scored();
            velocity = sf::Vector2f(150.f, 200.f);
        }
        puck.reset(sf::Vector2f(width_ / 2, height_ / 2), velocity);
        return true;
    }
    return false;
}

void World::render()
{
    mWindow.clear();

    mWindow.draw(left_border);
    mWindow.draw(right_border);
    mWindow.draw(top_border);

    mWindow.draw(puck.shape());
    mWindow.draw(left.shape());
    mWindow.draw(right.shape());

    board.render(mWindow);

    mWindow.display();
}


void World::reset()
{
    left.reset();
    right.reset();
    puck.reset(sf::Vector2f(width_ / 2, height_ / 2), sf::Vector2f(150.f, 200.f));
    board.reset();
}
