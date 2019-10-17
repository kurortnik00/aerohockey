#include <iostream>
#include <SFML/Graphics.hpp>

#include "game.hpp"

using namespace std;


float len2 (sf::Vector2f const v)
{
    return v.x * v.x + v.y * v.y;
}


float dot (sf::Vector2f const v1, sf::Vector2f const v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}


float dist2 (sf::Vector2f const & p1, sf::Vector2f const & p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}


Game::Game(float width, float height)
	: width_(width), height_(height), score_changed(false)
	, mWindow(sf::VideoMode(width, height), "Aerohockey", sf::Style::None)
    , puck (height / 20, sf::Color::White, sf::Vector2f(width / 2, height / 2), sf::Vector2f(150.f, 200.f))
    , left (height / 20, sf::Color(204, 0, 0), sf::Vector2f(100, height / 2), 250.f, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D)
	, right (height / 20, sf::Color(0, 102, 0), sf::Vector2f(width - 100, height / 2), 250.f, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right)
	, board (&left, &right, 5)
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

    balls = (Puck **) new Puck *[56];
    for (int i = 0; i < 56; i++)
    {
        balls[i] = new Puck(10.f, sf::Color::White, 
                            sf::Vector2f(100.f + 50.f * (i % 8), 100.f + 50.f * (i / 8)),
                            sf::Vector2f(150.f * (1 - 2 * (i % 2)), 200.f * (2 * (i % 2) - 1)));
    }
}


void Game::run()
{
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        elapsed += clock.restart();
        // cout << elapsed.asSeconds() << endl;
        
        while (elapsed > update_time)
        {
            processEvents();
            update();
            elapsed -= update_time;
        }
        
        render();
    }
}


void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                mWindow.close();
            }
        }    
    }

	left.handleInput();
	right.handleInput();
}


void Game::update()
{
	float delta = update_time.asSeconds();
    left.update(width_, height_, delta);
	right.update(width_, height_, delta);
    puck.update(width_, height_ - 60.f, delta);
    collide_objects(left, puck, width_, height_, delta);
	collide_objects(right, puck, width_, height_, delta);
	score_changed = goal_scored();
	board.update(delta, score_changed);
    /*
    for (int i = 0; i < 56; i++)
    {
		float delta = update_time.asSeconds();
        balls[i]->update(width_, height_, delta);
        for (int j = i + 1; j < 56; j++)
        {
            collide_objects(balls[i], balls[j], width_, height_, delta);
        }
    }
    */
}


void Game::collide_objects(Paddle & first, Puck & second, int width, int height, float delta)
{
    float r1 = first.radius();
    float r2 = second.radius();
    float threshold = (r1 + r2) * (r1 + r2);
    sf::Vector2f x1 = first.position(), x2 = second.position();
       
    if (dist2(x1, x2) <= threshold)
    {
        sf::Vector2f v1 = first.velocity(), v2 = second.velocity();     
        second.velocity() = v2 - (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);
		while (dist2(first.position(), second.position()) <= threshold)
		{
			second.update(width, height, delta);
		}
    }
}


void Game::collide_objects(Puck * first, Puck * second, int width, int height, float delta)
{
    float threshold = (first->radius() + second->radius()) * (first->radius() + second->radius());
    if (dist2(first->position(), second->position()) <= threshold)
    {
        sf::Vector2f v1 = first->velocity(), v2 = second->velocity();
        sf::Vector2f x1 = first->position(), x2 = second->position();
        
        first->velocity() = v1 - (x1 - x2) * dot(v1 - v2, x1 - x2) / len2(x1 - x2);
        second->velocity() = v2 - (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);

		while (dist2(first->position(), second->position()) <= threshold)
		{
			first->update(width, height, delta);
			second->update(width, height, delta);
		}
    }
}

bool Game::goal_scored()
{
	if ((puck.position().x < 0) || (puck.position().x > width_))
	{
		if (puck.position().x < 0)
		{
			right.scored();
		}
		else
		{
			left.scored();
		}
		puck.reset(sf::Vector2f(width_ / 2, height_ / 2));
		return true;
	}
	return false;
}

void Game::render()
{
    mWindow.clear();
    
	mWindow.draw(left_border);
	mWindow.draw(right_border);
	mWindow.draw(top_border);

    mWindow.draw(puck.shape());
    mWindow.draw(left.shape());
	mWindow.draw(right.shape());
    
	board.render(mWindow);
	/*
    for (int i = 0; i < 56; i++)
    {
        mWindow.draw(balls[i]->shape());
    }*/
    mWindow.display();
}
