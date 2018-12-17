#pragma once
#ifndef GAME_H
#define GAME_H

// Include dei file usati
#include "Grid.h"
#include "Drawer.h"
#include "ShipPlacer.h"

class Game{
    public:
        // Funzione chiamata alla partenza
        static void startingScreen();

        // Funzione chiamata dopo che sarà stata visualizzata
        // la schermata di partenza
        static void placingScreen();

        // Funzione chiamata dopo che sarà stata visuallzata
        // la schermata di piazzamento navi
        static void playingScreen();

    private:
        // Funzione per mantenere una referenza locale
        // al drawer
        static Drawer* drawer;

        // Puntatori alle griglie usate dal giocatore 1 e dal 
        // giocatore 2
        static Grid* player1;
        static Grid* player2;

        // Funzione usata per verificare se vi sono le condizione
        // per la sconfitta
        static bool lostCondition();
};

#endif