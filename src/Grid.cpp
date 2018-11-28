#include <iostream>
#include <vector>
#include "headers/Grid.h"
#include "headers/BaseElement.h"

using std::vector;

/**
 * Constructor for grid class
 */
Grid::Grid(int w, int h){
    // Setting grid size
    width = w;
    height = h;

    // Creating grid
    grid.resize(height);
    for(int y = 0; y < height; y++){
        grid[y].resize(width);
        for(int x = 0; x < width; x++){
            grid[y][x] = new BaseElement(x, y);
        }
    }
}

// Setting initial instance to NULL
Grid* Grid::instance = 0;

// Getter for the Grid instance
Grid* Grid::getInstance(int w, int h){
    if(instance==0){
        instance = new Grid(w, h);
    } else {
        std::cout << "WARNING: Grid already initialised!" << std::endl;
    }
}

int Grid::checkCell(int x, int y){
    grid[y][x]->getValue();
}

void Grid::setCell(int x, int y, int value){
    grid[y][x]->setValue(value);
}