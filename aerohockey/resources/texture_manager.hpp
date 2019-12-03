#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <cstring>
#include <SFML/Graphics.hpp>

#include "resource_manager.hpp"

struct TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
    TextureManager(const string & config_path);

    sf::Texture * load(const string & path);
};

#endif /* end of include guard: TEXTURE_MANAGER_HPP */
