#ifndef SHIP_H
#define SHIP_H

// Include degli header usati
#include "Grid.h"

class Ship{
    public:
        // Costruttore pubblico
        Ship(int*, int*, int, Grid*);

        // Metodo per verificare se una barca è viva
        bool isAlive();

        // Metodo per verificare la larghezza della barca
        int getSize();

        // Metodo per ottenre la coordinata dell' elemento iesimo
        int* getElement(int);

    private:
        // Puntatore ad un puntatore, punterà ad un array per le coordinata
        int** coordinates;

        // Valore della dimensione
        int size;

        // riferimento alla griglia in cui è piazzata
        Grid* grid;
};   

#endif