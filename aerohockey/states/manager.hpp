#pragma once

#include <unordered_map>

#include "../control/orbbec/astra/astra_wrapper.hpp"
#include "../objects/world.hpp"
#include "state.hpp"

using StateContainer = std::unordered_map<States::Type, State*>;

struct StateManager
{
    StateManager(const States::Type& initial, World & world, AstraWrapper& wrapper);
    ~StateManager();

    template <typename T>
    void registerState(const States::Type state, World & world);

    void activateState(const States::Type state);
    void processEvents();
    void update(const float delta);
    void render();

private:
    States::Type current_state;
    StateContainer container;
	AstraWrapper& astra_wrapper;
    World & world;
};
