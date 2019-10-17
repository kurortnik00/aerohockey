#pragma once

#include <SFML/Graphics.hpp>
#include "paddle.hpp"
#include "puck.hpp"
#include "board.hpp"

struct Game
{
public: 
    Game(float width, float height);
    void run();
    
private:
    void collide_objects(Puck * first, Puck * second, int width, int height, float delta);
    void collide_objects(Paddle & first, Puck & second, int width, int height, float delta);
	void processEvents();
    void render();
	bool goal_scored();
	void update();

    int width_, height_;
	bool score_changed;
    sf::RenderWindow mWindow;
    Puck puck;
    Paddle left, right;
	Scoreboard board;
    Puck ** balls;
	sf::RectangleShape left_border, top_border, right_border;
    const sf::Time update_time = sf::seconds(1.f / 60.f);
};