#pragma once

#include <string>
#include "paddle.hpp"

struct Scoreboard
{
public:
	Scoreboard(Paddle * left, Paddle * right, int gameDuration);
	void update(float delta, bool & score_changed);
	void render(sf::RenderWindow & window);

private:
	std::string time_line(float seconds);
	Paddle * left_;
	Paddle * right_;
	sf::RectangleShape left_score_border, right_score_border, main_border;
	float remainingTime_;
	sf::Font font_;
	sf::Text timer_, left_score, right_score, left_name, right_name;
};