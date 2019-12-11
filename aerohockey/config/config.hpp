#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Config
{
	// General
	extern float fps;
	extern float game_length;
	extern float screen_width, screen_height;
	extern bool kinectControl;

	// Game settings
	extern unsigned max_score;				// Scoring max_score times ends the game
	extern float game_length;				// Game length (in seconds)
	extern float game_start_delay;			// Delay for players to prepare

	// Colors
	extern sf::Color red, green;

	// Puck
	extern bool use_velocity_cap;			// If true, then puck speed is always <= max_velocity_cap
	extern float max_puck_velocity;			// Upper limit for puck speed if use_velocity_cap is true
	extern float initial_puck_velocity;		// Initial puck velocity when game starts or goal was scored
	extern float puck_radius;				// Radius of the puck


	// Collisions
	extern bool use_paddle_velocity;		// If true, then paddle velocity is used in collision physics
											// If false, paddle velocity is 0 during collision processing

	// Resources
	extern std::string font_scoreboard_path;	// Path to font for scoreboard
	extern std::string sound_scored_path;		// Path to 'scored' sound
	extern std::string sound_hit_path;			// Path to 'hit' sound
	extern std::string sound_wall_path;			// Path to 'wall' sound
	extern std::string texture_background_path;	// Path to background texture
}

#endif /* end of include guard: CONFIG_HPP */
