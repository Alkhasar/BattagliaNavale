#ifndef GAME_H
#define GAME_H

#include "Drawer.h"

class Game{

    private:
        static Drawer* drawer;

    public:
        static void introScreen();
        static void boatPlacer();
        static void gamePhase();

};

#endif