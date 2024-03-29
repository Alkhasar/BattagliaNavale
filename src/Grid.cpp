#include "headers/Grid.h"

Grid::Grid()
{
    clean(0);
}

Grid::~Grid()
{
    //dtor
}

//Imposta valore della casella di coordinate x,y
void Grid::setValue(int x, int y, int value)
{
    if(!isOutOfBounds(x, y))
        grid[y][x] = value;
}

//Imposta valore f in tutta la grid
void Grid::clean(int f){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            grid[i][j] = f;
        }
    }
}

//Fornisce valore della casella di coordinate x,y
int Grid::getValue(int x, int y)
{
    if(!isOutOfBounds(x, y))
        return grid[y][x];
    return -1;
}

//Verifica che la casella di coordinate x,y abbia un preciso valore
bool Grid::isValue(int x, int y, int value)
{
    if(!isOutOfBounds(x, y))
        return grid[y][x] == value;
    return false;
}

//Verifica che la casella di coordinate inserite appartenga alla griglia (true = fuori dalla grid)
bool Grid::isOutOfBounds(int x, int y)
{
    if(x >= 0 && x < 10 && y >= 0 && y < 10)
        return false;
    return true;
}

//Controlla la presenza di un valore tra due caselle (comprese) di coordinate specificate
//-1 = outOfBounds o diagonale, 0 = value non trovato, 1 = value trovato
int Grid::checkBetween(int x1, int y1, int x2, int y2, int value)
{
    if(isOutOfBounds(x1, y1) || isOutOfBounds(x2, y2))
        return -2;
    if(x1 == x2){
        for(int i = min(y1, y2); i < max(y1, y2); i++){
            if(grid[i][x1] == value)
                return 1;
        }
    } else if(y1 == y2) {
        for(int i = min(x1, x2); i < max(x1, x2); i++){
            if(grid[y1][i] == value)
                return 1;
            
        }
    } else {
        return -1;
    }
    return 0;
}

// Inserisce nave
//true = andata a buon fine
bool Grid::insertShip(int x1, int y1, int x2, int y2)
{
    if(x1 == x2){
        for(int i = min(y1, y2); i < max(y1, y2); i++){
                grid[i][x1] = 1;
        }
    } else if(y1 == y2) {
        for(int i = min(x1, x2); i < max(x1, x2); i++){
                grid[y1][i] = 1;
        }
    }
    return true;
}

// Restituisce minimo due valori
int Grid::min(int x1, int x2){
    if(x1>x2){
        return x2;
    }
    return x1;
}

//Restituisce max di due valori
int Grid::max(int x1, int x2){
    if(x1<x2){
        return x2;
    }
    return x1;
}

//Modifica valore casella in 2 (hit)
bool Grid::hit(int x, int y)
{
    if(!isValue(x,y,1))
        return false;
    else
        grid[y][x] = 2;
    return true;
}
