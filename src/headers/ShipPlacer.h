#pragma once
#ifndef SHIPPLACER_H
#define SHIPPLACER_H


// Include dei file usati
#include "Ship.h"
#include "Drawer.h"
#include <vector>

// Referenza locale di std:: per evitare di riscriverlo
using std::vector;

class ShipPlacer {
    public:
        // Costruttore chiamato per iniziare un piazzamento
        ShipPlacer(Grid&, vector<Ship*>&);

    private:
        // Variabili costanti per indicare il numero di navi da piazzare
        const int shipSizes[5]   = {1, 2, 3, 4, 5};
        const int shipNumbers[5] = {1, 2, 3, 2, 1};
        
        // Puntatori a variabili
        Grid* grid;
        Drawer* drawer;

        // Vettore per tenre traccia delle navi
        vector<Ship*> ships;

        // Funzione loop chiamata dal costruttore per piazzare le navi
        void loop();

        // Funzione per piazzare una nave
        int* placeShip(int);
};

#endif