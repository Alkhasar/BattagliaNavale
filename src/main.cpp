// Include di ncurses per chiamare le funzioni di uscita
#include <ncurses.h>

// Inclusione della classe gioco
#include "Game.cpp"

int main(int argc, char const *argv[])
{

    // Starting the game with the starting screen
    Game::startingScreen();

    endwin();
    exit(0);
    return 0;
}
