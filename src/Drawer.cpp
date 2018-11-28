#include <iostream>
#include "headers/Drawer.h"

using namespace std;

/**
 * Constructor for drawer singleton
 * 
 * This function will be called only once, and whill create the base 
 * graphic for the game.
 **/
Drawer::Drawer(){
    // Fetching console dimensions
    width = 80;
    height = 32;

    // Creating a 2D array
    rows = new string[height];

    // Initialize array to empty string array
    clear();
}

// Setting singleton instance to 0
Drawer* Drawer::instance = 0;

Drawer* Drawer::getInstance(){
    if(instance==0){
        instance = new Drawer();
    }
    return instance;
}

void Drawer::setRow(int row, string c){
    rows[row] = c;
}

int Drawer::getCenterX(){
    return (int) width/2;
}

int Drawer::getCenterY(){
    return (int) height/2;
}

void Drawer::draw(){
    cleanConsole();
    for(int row = 0; row < height; row++){
        cout << rows[row] << endl;
    }
}

void Drawer::clearRow(int row){
    rows[row] = "";
}

void Drawer::clear(){
    for(int y = 0; y < height; y++){
        clearRow(y);
    }
}

void Drawer::addEmptyRows(int row, int rows){
    for(int i = row; i < row + rows; i++){
        setRow(row, "\n");
    }
}

void Drawer::addFilledRow(int row, string c){
    string str = "";
    for(int i = 0; i < width; i++){
        str += c;
    }
    setRow(row, str);
}

void Drawer::cleanConsole(){
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\033[2J\033[1;1H";
}