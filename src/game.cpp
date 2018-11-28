#include <iostream>
#include "headers/Game.h"
#include "headers/Drawer.h"

using namespace std;

Drawer* Game::drawer = Drawer::getInstance();

void Game::introScreen(){
    // Variable initialization
    drawer->addFilledRow(0, "=");
    drawer->addEmptyRows(1, 2);
    drawer->setRow(3, "Benvenuti a battaglia navale");

    drawer->draw();

}