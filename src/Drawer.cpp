// Including header file
#include "headers/Drawer.h"

// Including external libraries
#include <ncurses.h>
#include <iostream>
#include "Grid.cpp"

using std::string;
using std::to_string;

Drawer* Drawer::instance = 0;

Drawer* Drawer::getInstance(){
    if(instance == 0){
        instance = new Drawer(); 
    }
    return instance;
}

Drawer::Drawer(){
    // Initialising ncurses lib
    initscr();
    noecho();
    console = newwin(0, 0, 0, 0);

    // Constant Data
    int rows = 24;
    int cols = 80;

    // Setting cursor position
    ptr = new int[2]{30, 4};

    // Creating a pointer array to sizes
    size = new int[2]{cols, rows}; 
   
    // Inital screen update
    update();
}

int Drawer::pause(){
    return wgetch(console);
}

void Drawer::update(){
    drawBoundaries(ACS_S7, ACS_VLINE);
    refresh();
    wrefresh(console);
}

void Drawer::drawBoundaries(chtype horizontal, chtype vertical){
    box(console, vertical, horizontal);
}

void Drawer::clearConsole(){
    wclear(console);
    update();
}

void Drawer::drawTitle(string title){
    int len = title.size();
    mvwprintw(console, 1, size[0]/2 - len/2, title.c_str());
    update();
}

void Drawer::drawGrid(Grid* grid){
    string row = "   0 1 2 3 4 5 6 7 8 9";
    mvwprintw(console, 3, size[0]/2 - row.size()/2, row.c_str());
    row = "   _ _ _ _ _ _ _ _ _ _";
    mvwprintw(console, 4, size[0]/2 - row.size()/2, row.c_str());

    for(int y = 0; y < 10; y++){
        row = to_string(y) + "| ";
        for(int x = 0; x < 10; x++){
            switch(grid->getValue(x, y)){
                case 0:
                    row += ". ";
                    break;
                case 1:
                    row += "0 ";
                    break;
                case 2:
                    row += "X ";
                    break;
                case 3:
                    row += "* ";
                    break;
                case -1:
                    row += "? ";
                    break;    
            }
        }
        mvwprintw(console, 5+y, size[0]/2 - row.size()/2, (row + "|").c_str());
    }
    row = "   _ _ _ _ _ _ _ _ _ _";
    mvwprintw(console, 15, size[0]/2 - row.size()/2, row.c_str());
    update();
}

int Drawer::drawInteraction(string sentence, int case1, int case2){
    drawSentence(sentence.c_str());
    int c = -1;
    while(c != case1 && c != case2){
        c = pause();
    }
    return c;
}

string Drawer::drawInteraction(string sentence, string case1, string case2){
    drawSentence(sentence.c_str());
    string c = "DoNt TyPe ThIs tO Avoid ErrOrs!";
    while(c != case1 && c != case2){
        c = pause();
    }
    return c;
}

void Drawer::drawRules(){
    drawSentence(4, 5, "BENVENUTO A BATTAGLIA NAVALE");
    drawSentence(4, 6, "Le regole del gioco sono semplici, ogni giocatore ha a");
    drawSentence(4, 7, "disposizione: ");
    drawSentence(4, 9, "    - PORTAREI           Caselle: 6 Quantità: 1");
    drawSentence(4, 10, "    - CORAZZATA          Caselle: 5 Quantità: 1");
    drawSentence(4, 11, "    - INCROCIATORE       Caselle: 4 Quantità: 3");
    drawSentence(4, 12, "    - SOTTOMARINO        Caselle: 3 Quantità: 4");
    drawSentence(4, 13, "    - CACCIATORPEDINIERE Caselle: 2 Quantità: 3");
    drawSentence(4, 14, "    - SCIALUPPA          Caselle: 1 Quantità: 1");
    drawSentence(4, 16, "lo scopo è distruggere tutte le navi dell'avversario.");
    drawSentence(4, 17, "L'unico accorgimento è che non bisogna guardare mentre");
    drawSentence(4, 18, "l'avversario posiziona le barche.");
}

void Drawer::drawSentence(string sentence){
    wmove(console, 21, 4);
    wclrtoeol(console);
    wprintw(console, sentence.c_str());
    update();
}

void Drawer::drawSentence(int x, int y, string sentence){
    wmove(console, y, x);
    wclrtoeol(console);
    wprintw(console, sentence.c_str());
    update();
}

int* Drawer::moveCursor(bool &enter){
    int c = pause();
    switch(c){
        case 65:
            ptr = new int[2]{ptr[0], ptr[1] - 1};
            break;
        
        case 66:
            ptr = new int[2]{ptr[0], ptr[1] + 1};
            break;

        case 68:
            ptr = new int[2]{ptr[0] - 2, ptr[1]};
            break;

        case 67:
            ptr = new int[2]{ptr[0] + 2, ptr[1]};
            break;
        
        case 10:
            enter = true;
            break;

        default:
            //drawSentence(to_string(KEY_UP)+" "+to_string(ptr[0]) + " - " + to_string(ptr[1]) +" "+ to_string(c) + " "+ to_string(c==KEY_UP));
            break;
    }

    if(ptr[0] >= xMax){
        ptr[0] -= 2;
    } else if(ptr[0] < xMin){
        ptr[0] += 2;
    }

    if(ptr[1] >= yMax){
        ptr[1] -= 1;
    } else if(ptr[1] < yMin){
        ptr[1] += 1;
    }

    wmove(console, ptr[1], ptr[0]);
    update();

    return new int[2]{ptr[0], ptr[1]};
}

void Drawer::moveCursor(int* pos){
    wmove(console, pos[1], pos[0]);
    update();
}

int* Drawer::moveCursor(bool &enter, int size, bool &esc, int* center){
    int c = pause();
    switch(c){
        case 65:
            if(center[1] - size > yMin - 2){
                ptr = new int[2]{center[0], center[1] - size + 1};
            }
            break;
        
        case 66:
            if(center[1] + size < yMax + 1){
                ptr = new int[2]{center[0], center[1] + size - 1};
            }
            break;

        case 68:
            if(center[0] - 2*size > xMin - 4){
                ptr = new int[2]{center[0] - 2*(size-1), center[1]};
            }
            break;

        case 67:
            if(center[0] + 2*size < xMax + 2){
                ptr = new int[2]{center[0] + 2*(size-1), center[1]};
            }
            break;
        
        case 127:
            esc = true;
            break;

        case 10:
            enter = true;
            break;  

        default:
            //drawSentence(to_string(KEY_UP)+" "+to_string(ptr[0]) + " - " + to_string(ptr[1]) +" "+ to_string(c) + " "+ to_string(c==KEY_UP));
            break;
    }     

    wmove(console, ptr[1], ptr[0]);
    update();
    
    return new int[2]{ptr[0], ptr[1]};
}