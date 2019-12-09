#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

#include "world.hpp"
#include "../util.hpp"

using namespace std;


World::World(float width, float height, float update_time, BodyTracker & kinect, bool kinectControl)
    : width_(width)
    , height_(height)
    , score_changed(false)
    , paused(false)
    , use_paddle_velocity(true)
	, use_velocity_cap(true)
    , kinectControl (kinectControl)
    , puck_velocity (sf::Vector2f(400.f, 400.f))
    , update_time (update_time)
	, max_puck_velocity(800.f)
    , mWindow(sf::VideoMode(width, height), "Aerohockey", sf::Style::None)
    , puck (height / 20, sf::Color::White, sf::Vector2f(width / 2, height / 2), puck_velocity)
    , left (height / 20, sf::Color(204, 0, 0), update_time, kinect, true, kinectControl)
    , right (height / 20, sf::Color(0, 102, 0), update_time, kinect, false, kinectControl)
    , board (&left, &right, 0.5)
    , left_ready (sf::Vector2f(width / 4, height / 2), sf::Vector2f(width / 10, width / 10))
    , right_ready (sf::Vector2f(width * 3 / 4, height / 2), sf::Vector2f(width / 10, width / 10))
{
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);

    std::string scored_path = getcwd_string() + "/media/sounds/scored.wav";
    if (!scored.loadFromFile(scored_path))
    {
        LOG(ERROR) << "Failed to load 'scored' sound: " << scored_path << "\n";
    }
    else
    {
        scored_sound.setBuffer(scored);
    }

    std::string hit_path = getcwd_string() + "/media/sounds/hit.wav";
    if (!hit.loadFromFile(hit_path))
    {
        LOG(ERROR) << "Failed to load 'hit' sound: " << hit_path << "\n";
    }
    else
    {
        hit_sound.setBuffer(hit);
    }

    std::string wall_path = getcwd_string() + "/media/sounds/wall.wav";
    if (!wall.loadFromFile(wall_path))
    {
        LOG(ERROR) << "Failed to load 'wall' sound: " << wall_path << "\n";
    }
    else
    {
        wall_sound.setBuffer(wall);
    }

    std::string path = getcwd_string() + "/media/textures/bg-space.jpg";
    if (!bg_texture.loadFromFile(path))
    {
        LOG(ERROR) << "Failed to load texture: " << path << "\n";
    }
    else
    {
        background.setTexture(bg_texture);
        background.setScale(width_ / background.getLocalBounds().width,
                            height_ / background.getLocalBounds().height);
    }

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(width_ / 2, height_));
    left_border.setFillColor(sf::Color::Transparent);
    left_border.setOutlineColor(sf::Color(242, 99, 80, 200));
    left_border.setOutlineThickness(-10.f);

    right_border.setPosition(width_ / 2, 0.f);
    right_border.setSize(sf::Vector2f(width_ / 2, height_));
    right_border.setOutlineColor(sf::Color(102, 214, 92, 200));
    right_border.setFillColor(sf::Color::Transparent);
    right_border.setOutlineThickness(-10.f);
}


void World::processEvents()
{
    if (!kinectControl)
    {
        left.handleInput();
        right.handleInput();
    }
}


void World::update()
{
    left.update();
    right.update();
    puck.update(update_time);

    for (int i = 0; i < left.n_limbs; i++)
    {
        collide_objects(left.paddles()[i], puck);
    }
    for (int i = 0; i < right.n_limbs; i++)
    {
        collide_objects(right.paddles()[i], puck);
    }
    puck.walls_collide(width_, height_, wall_sound);

    score_changed = goal_scored();
    board.update(update_time, score_changed);
}


void World::collide_objects(Paddle & first, Puck & second)
{
    float r1 = first.radius();
    float r2 = second.radius();
    float threshold = (r1 + r2) * (r1 + r2);
    sf::Vector2f x1 = first.position(), x2 = second.position();

    float dist = dist2(x1, x2);
    if (dist2(x1, x2) <= threshold)
    {
        sf::Vector2f v1 = sf::Vector2f(0.f, 0.f), v2 = second.velocity();
        if (use_paddle_velocity)
        {
            v1 = first.velocity();
        }

        float rewind_time = 0.f;
        if (dist < threshold)
        {
            sf::Vector2f dv = v1 - v2;
            rewind_time = (r1 + r2 - sqrt(dist)) / sqrt(len2(dv));

            first.moveTo(x1 - rewind_time * v1);
            second.moveTo(x2 - rewind_time * v2);
        }

        sf::Vector2f x1 = first.position(), x2 = second.position();
        second.velocity() = v2 - 2.f * (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);

		if (use_velocity_cap)
		{
			float velocity_module = sqrt(len2(second.velocity()));
			LOG(INFO) << velocity_module;
			if (velocity_module > max_puck_velocity)
			{
				float scale = max_puck_velocity / velocity_module;
				second.velocity() *= scale;
				LOG(INFO) << "Scaled by " << scale << " - vx: " << second.velocity().x
					<< ", vy: " << second.velocity().y;
			}
		}

        // first.update(width, height, rewind_time);
        second.update(rewind_time);
        hit_sound.play();
    }
}

bool World::goal_scored()
{
    sf::Vector2f velocity = puck_velocity;

    if ((puck.position().x < 0) || (puck.position().x > width_))
    {
        if (puck.position().x < 0)
        {
            right.scored();
            velocity.x *= -1;
        }
        else
        {
            left.scored();
        }
        puck.reset(sf::Vector2f(width_ / 2, height_ / 2), velocity);
        scored_sound.play();
        return true;
    }
    return false;
}

void World::render()
{
    mWindow.clear();

    mWindow.draw(background);

    mWindow.draw(left_border);
    mWindow.draw(right_border);

    left.render(mWindow);
    right.render(mWindow);
    puck.render(mWindow);

    board.render(mWindow);

    mWindow.display();
}


void World::reset()
{
    left.reset();
    right.reset();
    puck.reset(sf::Vector2f(width_ / 2, height_ / 2), puck_velocity);
    board.reset();
}
