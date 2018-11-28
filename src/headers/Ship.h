#ifndef SHIP_H
#define SHIP_H

#include "BaseElement.h"

class Ship{
    private:
        // Ship size
        int size;
        
        // Coordinates of the top-left corner
        int x;
        int y;

        // Array pointing to baseElements
        BaseElement** children;

    public:
        Ship(int, int, int);
        bool isDestroyed();
        void addBaseElements(BaseElement*, int);

};

#endif