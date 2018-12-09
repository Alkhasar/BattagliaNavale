// Include degli header usati
#include "headers/Ship.h"
#include "headers/Grid.h"

Ship::Ship(int* sp, int* fp, int _size, Grid* _grid){
    // Assegnazione dei parametri
    grid = _grid;
    size = _size;

    // Creazione delle coordinate della barca
    *coordinates = new int[size]();
    if(sp[0] == fp[0]){
        for(int i = 0; i < size; i++){
                coordinates[i] = new int[2]{sp[0], sp[1] + i};
        }
    } else if(sp[1] == fp[1]) {
        for(int i = 0; i < size; i++){
                coordinates[i] = new int[2]{sp[0] + 1, sp[1]};
        }
    }
}

bool Ship::isAlive(){
    // Premessa: Se almeno un pezzo è vivo la nave è viva
    for(int i = 0; i < size; i++){
        if(grid->getValue(coordinates[i][0], coordinates[i][1]) == 1){
            return true;
        }
    }
    return false;
}

int Ship::getSize(){
    return size;
}

int* Ship::getElement(int i){
    return coordinates[i];
}