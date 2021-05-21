#include"game.h"

int main(){
    Game game;

    // Main loop
    while (game.getWindowIsOpen())
    {   
        // Checking events
        game.checkEvents();
        // Game logic
        game.update();
        // Rendering and drawing
        game.renderFrame();
    }

    return 0;
}
