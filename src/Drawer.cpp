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

    // Impostazione dei colori
    start_color();

    // Associazione allo slot 1 del colore BLU come foreground
    // E CIANO come background.
    init_pair(1, COLOR_BLUE, COLOR_CYAN);

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
    // Partenza della colorazione
    wattron(console, COLOR_PAIR(1));
    box(console, vertical, horizontal);
    // Chiusura della colorazione
    wattroff(console, COLOR_PAIR(1));
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
    drawSentence(4, 5,  "BENVENUTO A BATTAGLIA NAVALE!");
    drawSentence(4, 6,  "Le regole del gioco sono semplici, ogni giocatore ha a");
    drawSentence(4, 7,  "disposizione: ");
    drawSentence(4, 9,  "    - CORAZZATA          Caselle: 5 Quantità: 1");
    drawSentence(4, 10, "    - INCROCIATORE       Caselle: 4 Quantità: 2");
    drawSentence(4, 11, "    - SOTTOMARINO        Caselle: 3 Quantità: 2");
    drawSentence(4, 12, "    - CACCIATORPEDINIERE Caselle: 2 Quantità: 2");
    drawSentence(4, 13, "    - SCIALUPPA          Caselle: 1 Quantità: 1");
    drawSentence(4, 14, "NON PREMERE LE FRECCE DIREZIONALI SE NON RICHIESTO, GRAZIE.");
    drawSentence(4, 15, "Lo scopo è distruggere tutte le navi dell'avversario!");
    drawSentence(4, 16, "Ci si muove nella griglia con le frecce direzionali.");
    drawSentence(4, 17, "Per bombardare si preme ENTER.");
}

void Drawer::drawRulesPlacer(){
    drawSentence(4, 5,  "Il gioco farà posizionare le barche dalla più");
    drawSentence(4, 6,  "piccola alla più grande.");
    drawSentence(4, 7,  "Il giocatore, muovendo il cursore con le frecce direzionali,");
    drawSentence(4, 8,  "si dovrà posizionare sulla casella in cui ci sarà la prua");
    drawSentence(4, 9,  "della nave da piazzare, fatto ciò dovrà confermare premendo ENTER.");
    drawSentence(4, 10, "Dunque dovrà posizionare il cursore sulla casella");
    drawSentence(4, 11, "in cui ci sarà la poppa della nave e riconfermare con ENTER");
    drawSentence(4, 12, "Questo andrà fatto per tutte le navi");
    drawSentence(4, 13, "Ovviamente per le barche lunghe 1 poppa e prua coincidono, sarà");
    drawSentence(4, 14, "quindi necessaria una sola azione");
    drawSentence(4, 15, "Per annullare il posizionamento della barca e quindi scegliere");
    drawSentence(4, 16, "un'altra casella premere BACKSPACE");
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