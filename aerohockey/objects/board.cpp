#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "board.hpp"

using namespace std;

Scoreboard::Scoreboard(Player * left, Player * right, float gameDuration)
    : left_ (left), right_ (right), gameDuration_ (gameDuration)
{
    remainingTime_ = gameDuration_;
    std::string path = getcwd_string() + Config::font_scoreboard_path;
    if (!font_.loadFromFile(path))
    {
        LOG(ERROR) << "Failed to load font for scoreboard: " << path;
    }
    else
    {
        LOG(INFO) << "Successfully loaded font for scoreboard: " << path;
        left_score.setFont(font_);
        timer_.setFont(font_);
        right_score.setFont(font_);
    }

    float x = 120.f, y = 60.f;

    left_score_border.setPosition(Config::screen_width / 2 - x / 2 - y, Config::screen_height - 60.f);
    left_score_border.setSize(sf::Vector2f(y, 60.f));
    left_score_border.setFillColor(Config::red);
    left_score_border.setOutlineColor(sf::Color::White);
    left_score_border.setOutlineThickness(-2.f);

    right_score_border.setPosition(Config::screen_width / 2 + x / 2, Config::screen_height - 60.f);
    right_score_border.setSize(sf::Vector2f(y, 60.f));
    right_score_border.setFillColor(Config::green);
    right_score_border.setOutlineColor(sf::Color::White);
    right_score_border.setOutlineThickness(-2.f);

    time_border.setPosition(Config::screen_width / 2 - x / 2, Config::screen_height - 60.f);
    time_border.setSize(sf::Vector2f(x, 60.f));
    time_border.setFillColor(sf::Color::Transparent);
    time_border.setOutlineColor(sf::Color::White);
    time_border.setOutlineThickness(-2.f);
    
    left_score.setCharacterSize(40);
    left_score.setPosition(300.f, 545.f);
    left_score.setFillColor(sf::Color::White);
    left_score.setString(to_string(left_->score()));

    timer_.setCharacterSize(40);
    timer_.setPosition(342.f, 545.f);
    timer_.setFillColor(sf::Color::White);
    timer_.setString(time_line(remainingTime_));

    right_score.setCharacterSize(40);
    right_score.setPosition(480.f, 545.f);
    right_score.setFillColor(sf::Color::White);
    right_score.setString(to_string(right_->score()));
}

string Scoreboard::time_line(float seconds)
{
    int mins = (int) seconds / 60;
    int secs = (int) seconds % 60;
    sprintf(t_, "%02d:%02d", mins, secs);

    return t_;
}

void Scoreboard::update(float delta, bool & score_changed)
{
    if (score_changed)
    {
        left_score.setString(to_string(left_->score()));
        right_score.setString(to_string(right_->score()));
        score_changed = false;
    }
    remainingTime_ -= delta;
    timer_.setString(time_line(remainingTime_));
}

void Scoreboard::render(sf::RenderWindow & window)
{
    window.draw(left_score_border);
    window.draw(right_score_border);
    window.draw(time_border);

    window.draw(left_score);
    window.draw(timer_);
    window.draw(right_score);
}

void Scoreboard::reset()
{
    remainingTime_ = gameDuration_;
    left_score.setString(to_string(0));
    right_score.setString(to_string(0));
}
