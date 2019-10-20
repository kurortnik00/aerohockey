#include <SFML/Main.hpp>
#include "game.hpp"


int main()
{
    Game game(800.f, 600.f);
    game.run();

	return EXIT_SUCCESS;
}
