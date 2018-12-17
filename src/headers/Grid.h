#ifndef GRID_H
#define GRID_H


class Grid
{
    public:
        Grid();
        virtual ~Grid();

        void setValue(int x, int y, int value); //Imposta valore in x,y
        int getValue(int x, int y);      //Fornisce il valore di x,y
        bool isValue(int x, int y, int value); //Verifica se il valore in x,y è quello atteso
        bool isOutOfBounds(int x, int y); //Controlla se x,y appartiene alla griglia (true = fuori)
        int checkBetween(int x1, int y1, int x2, int y2, int value); //Controlla la presenza di un valore tra due caselle 
        bool insertShip(int, int, int, int); //Inserisce nave
        bool hit(int x, int y); //Colpisce casella 
        void clean(int); //Cambia valore a tutta la grid

    private:
        const int HEIGHT = 10; //Dimensioni grid
        const int WIDTH = 10;
        int grid[10][10];  //Inizializza grid
        int min(int, int); 
        int max(int, int);
};

#endif // GRID_H
