#include "config.hpp"

namespace Config
{
    // General
    float fps = 120.f;
    float screen_width = 800.f;
    float screen_height = 600.f;
    bool kinectControl = false;

    // Game settings
    unsigned max_score = 5;
    float game_length = 180.f;
    float game_start_delay = 1.f;

    // Colors
    sf::Color red = sf::Color(204, 0, 0);
    sf::Color green = sf::Color(0, 102, 0);

    // Puck
    bool use_velocity_cap = true;
    float max_puck_velocity = 800.f;
    float initial_puck_velocity = 400.f;
    float puck_radius = screen_height / 20.f;

    // Collisions
    bool use_paddle_velocity = true;

    // Resources
    std::string font_scoreboard_path = "/media/fonts/DIN.ttf";
    std::string sound_scored_path = "/media/sounds/scored.wav";
    std::string sound_hit_path = "/media/sounds/hit.wav";
    std::string sound_wall_path = "/media/sounds/wall.wav";
    std::string texture_background_path = "/media/textures/bg-space.jpg";
}