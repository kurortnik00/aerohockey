#pragma once

#include <string>
#include "paddle.hpp"

struct Scoreboard
{
public:
    Scoreboard(Paddle * left, Paddle * right, float gameDuration);
    void update(float delta, bool & score_changed);
    void render(sf::RenderWindow & window);
    void reset();

private:
    std::string time_line(float seconds);
    char t_[8];
    Paddle * left_;
    Paddle * right_;
    sf::RectangleShape left_score_border, right_score_border, main_border;
    float remainingTime_, gameDuration_;
    sf::Font font_;
    sf::Text timer_, left_score, right_score, left_name, right_name;
};
