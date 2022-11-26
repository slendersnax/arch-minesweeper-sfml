#include <SFML/Graphics.hpp>
#include "classes/Game.h"

int main() {
    Game game = Game();
    game.init();
    game.mainLoop();

    return 0;
}
