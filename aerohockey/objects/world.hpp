#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../control/kinect/body_tracker.h"
#include "../easylogging/easylogging++.h"
#include "board.hpp"
#include "player.hpp"
#include "puck.hpp"
#include "ready_button.hpp"

struct World
{
public:
    World(float width, float height, float update_time, BodyTracker & kinect, bool kinectControl);
    void processEvents();

    void collide_objects(Paddle & first, Puck & second);
    void render();
    void reset();
    bool goal_scored();
    void update();

    int width_, height_;
	float update_time, max_puck_velocity;
    bool score_changed, paused, kinectControl, use_paddle_velocity, use_velocity_cap;
    sf::RenderWindow mWindow;
    sf::Sprite background;
    sf::Texture bg_texture;
    sf::SoundBuffer scored, hit, wall;
    sf::Sound scored_sound, hit_sound, wall_sound;
    sf::Vector2f puck_velocity;
    Puck puck;
    Player left, right;
    Scoreboard board;
    ReadyButton left_ready, right_ready;
    sf::RectangleShape left_border, top_border, right_border;
};
