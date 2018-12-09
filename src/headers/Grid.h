#ifndef GRID_H
#define GRID_H


class Grid
{
    public:
        Grid();
        virtual ~Grid();

        void setValue(int x, int y, int value);
        int getValue(int x, int y);
        bool isValue(int x, int y, int value);
        bool isOutOfBounds(int x, int y); //private se non utilizzato fuori
        int checkBetween(int x1, int y1, int x2, int y2, int value);
        bool insertShip(int, int, int, int);
        bool hit(int x, int y);
        void clean(int);

    private:
        const int HEIGHT = 10;
        const int WIDTH = 10;
        int grid[10][10];
        int min(int, int);
        int max(int, int);
};

#endif // GRID_H
