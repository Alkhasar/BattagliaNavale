#ifndef DRAWER_H  
#define DRAWER_H

#include <iostream>

using std::string;

class Drawer
{
    public:
        // Function to draw the grid onScreen
        void draw();

        // Function to set a char to grid's x, y position
        void setRow(int, string);
        
        // Getter for singleton instance
        static Drawer* getInstance();

        // Function to clear drawing array
        void clearRow(int);
        void clear();

        // Getters for center position
        int getCenterX();
        int getCenterY();

        // Method for creating empty rows
        void addEmptyRows(int, int);

        // Method to add a row full of a symbol
        void addFilledRow(int, string);

    private:
        // Singleton pattern
        Drawer();
        static Drawer* instance;

        // Sized of the console
        int width;
        int height;

        // Array to draw to console
        string* rows;

        // cleaning console method
        void cleanConsole();
};

#endif