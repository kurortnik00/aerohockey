#include "resource_manager.hpp"

ResourceManager::~ResourceManager()
{
    while (resources.begin() != resources.end()) {
        delete resources.begin()->second;
        resources.erase(resources.begin());
    }
}
