#pragma once

#include <SFML/Graphics.hpp>
//#include "BodyBasics.h"

struct Paddle
{
public:
    Paddle(float radius, sf::Color color, sf::Vector2f position, float velocity,
           sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
    void update(int width, int height, float delta);
    void handleInput();
    sf::CircleShape shape();
    float radius();
    sf::Vector2f & position();
    sf::Vector2f & velocity();
	unsigned score();
	void scored();

private:
    void stop();
    sf::CircleShape shape_;
    float radius_;
    sf::Color color_;
    sf::Vector2f position_;
    sf::Vector2f current_velocity_;
	unsigned score_;
	float velocity_, vx_, vy_;
    sf::Keyboard::Key const up_, down_, left_, right_;
//	CBodyBasics kinectApplication;

	enum {
		SPINEBASE,
		SPINEMID,
		NECK,
		HEAD,
		SHOULDERLEFT,
		ELBOWLEFT,
		WRISTLEFT,
		HANDLEFT,
		SHOULDERRIGHT,
		ELBOWRIGHT,
		WRISTRIGHT,
		HANDRIGHT,
		HIPLEFT,
		KNEELEFT,
		ANKLELEFT,
		FOOTLEFT,
		HIPRIGHT,
		KNEERIGHT,
		ANKLERIGHT,
		FOOTRIGHT,
		SPINESHOULDER,
		HANDTIPLEFT,
		THUMBLEFT,
		HANDTIPRIGHT,
		THUMBRIGHT,
	};
};
