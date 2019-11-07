#pragma once

#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "paddle.hpp"
#include "puck.hpp"
#include "ready_button.hpp"

struct World
{
public:
    World(float width, float height);
    void processEvents();

    void collide_objects(Puck * first, Puck * second, int width, int height);
    void collide_objects(Paddle & first, Puck & second, int width, int height, float delta);
    void render();
    void reset();
    bool goal_scored();
    void update(const float delta);

    int width_, height_;
    bool score_changed, paused;
    sf::RenderWindow mWindow;
    Puck puck;
    Paddle left, right;
    Scoreboard board;
    ReadyButton left_ready, right_ready;
    sf::RectangleShape left_border, top_border, right_border;
};
