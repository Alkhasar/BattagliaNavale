#ifndef GRID_H  
#define GRID_H

#include <vector>
#include "BaseElement.h"

using std::vector;

class Grid{
    public:
        // Getter that return 0 or the baseElement at position x,y
        int checkCell(int, int);

        // Setter for position x, y of the grid
        void setCell(int, int, int);

        // Getter for the Grid instance;
        static Grid* getInstance(int, int);

    private:
        Grid(int, int);
        static Grid* instance;

        // Size of the grid
        int width;
        int height;

        vector<vector<BaseElement*>> grid;
};

#endif
