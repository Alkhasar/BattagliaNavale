#pragma once
#ifndef DRAWER_H
#define DRAWER_H

// Include dei file usati
#include <iostream>
#include <ncurses.h>

// Referenza locale di std:: per evitare di riscriverlo
using std::string;

class Drawer{
    public:
        // Metodo per disegnare il titolo
        void drawTitle(string);

        // Metodo per disegnare la griglia
        void drawGrid(Grid*);

        // Metodo per visuallizare le regole
        void drawRules();

        // Metodo per ripulire la console e ridisegnare i bordi
        void clearConsole();

        // Metodo per fare un refresh dalla console
        void update();

        // Metodo che può essere usato sia per leggere un tasto premuto
        // sia per mettere in pausa il gioco
        int pause();

        // Overloading del metodo draw sentence
        // Disegna una frase in posizione predefinita
        void drawSentence(string);

        // Disegna una frase in una posizione data {x, y}
        void drawSentence(int, int, string);

        // Overloading del move cursor
        // Muove il cursore alla posizione del vettore{x, y}
        void moveCursor(int*);

        // Muove il cursore entro la griglia e cambia il valore
        // del parametro passato in true se enter viene premuto
        int* moveCursor(bool&);

        // Muove il cursore entro i parametri e tenendo un punto
        // centrale fisso, cambia il valore del primo bool se viene premuto
        // enter, e  del secondo se viene premuto backspace
        int* moveCursor(bool&, int, bool&, int*);

        // Overlaoding del drawInteraction
        // Funzione che richiede un input da parte dell'utente
        int drawInteraction(string, int, int);
        string drawInteraction(string , string , string);

        // Design pattern del signleton
        static Drawer* getInstance();
        

    private:
        // Design pattern del singleton
        Drawer();
        static Drawer* instance;

        // Refrenza locale della variabile WINDOW di ncurses
        WINDOW* console;

        // Metodo per disgnare i bordi
        void drawBoundaries(chtype, chtype);

        // Puntatori alle dimensioni della console
        int* size;
        int* ptr;

        // Posizioni limite della griglia
        int xMin = 32; 
        int yMin = 5; 
        int xMax = 51; 
        int yMax = 15;

};

#endif