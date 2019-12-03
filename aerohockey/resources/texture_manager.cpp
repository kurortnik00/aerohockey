#include <cstring>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "texture_manager.hpp"

TextureManager::TextureManager(const string & config_path)
    : ResourceManager(config_path)
{

}

sf::Texture * TextureManager::load(const string & path)
{
    sf::Texture* texture = new sf::Texture();

    if (!texture->loadFromFile(path))
    {
        delete texture;
        texture = nullptr;
        std::cerr << "Failed to load texture: " << path << "\n";
    }

    return texture;
}
