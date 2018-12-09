// Include degli header
#include "headers/ShipPlacer.h"

// Including external lib
#include "Drawer.cpp"
#include "Ship.cpp"
#include <vector>

using std::vector;

ShipPlacer::ShipPlacer(Grid & _grid, vector<Ship*> & _ships){
    // Assegnazione dei parametri passati
    grid = &_grid;
    ships = _ships;

    // Assegnazione del disegnatore
    drawer = Drawer::getInstance();

    // Disegno della griglia
    drawer->drawGrid(grid);
    loop();
}

void ShipPlacer::loop(){  
    // Loop su ogni nave e piazzamento :: DA MIGLIORARE
    for(int size = 1; size < 6; size++){
        for(int ship = 0; ship < shipNumbers[size - 1]; ship++){
            // Viene tenuta traccia della posizione finle della nave
            // per muoverci il cursore appena piazzata
            int* pos = placeShip(size);

            // Disegno della griglia e riposizionamento del cursore
            drawer->drawGrid(grid);
            drawer->moveCursor(pos);
        }
    }

    // Verifica che l'utente sia soddisfatto del posizionamento
    string answear = drawer->drawInteraction("Vuoi mantenere la griglia come è stata posizionata? (y / n)", "y", "n");
    if(answear == "n"){
        grid->clean(0);
        drawer->drawGrid(grid);
        loop();
    }
}

int* ShipPlacer::placeShip(int size){
    // Variabile che indica se il posizionamento è avvenuto con successo
    bool done = true;

    // Creazione di pos2 in uno scope più largo, per essere successivamente 
    // restituita senza problemi
    int* pos2;


    while(done){    
        // Variabile che indica se il tasto enter è stato premuto
        bool enter = false;

        // Movimento libero del cursore entro la griglia
        int* pos1 = drawer->moveCursor(enter);
        
        // Verifica che non si sta selezionando una casella gia nave
        if(grid->getValue(pos1[0], pos1[1]) == 1){
            enter = false;
        }

        // Verifica della pressione del tasto enter
        if(enter == true){
            // Variabile che indica se la nave è stata piazzata con successo
            bool placed = false;

            // Variabile che indica se è stato richiesto un escape
            bool esc = false;

            // Scelta della direzione della nave se la larghezza è > 1
            if(size > 1){
                // Loop eseguito fintato che enter o esc non sono premuti
                while ((!placed) && (!esc)) {
                    // Ottenimento della seconda coordinata della nave
                    pos2 = drawer->moveCursor(placed, size, esc, pos1);

                    // Verifica che non sia illegale
                    if(placed){
                        if(grid->checkBetween((pos1[0] - 31) / 2, pos1[1] - 5, (pos2[0] - 31) / 2, pos2[1] - 5, 1) == 1){
                            placed = false;
                            pos2 = new int[2]{0, 0};
                            drawer->drawSentence("La nave collide con una piazzata in precedenza. Posizione non valida!");
                        } else if(pos1[0] == pos2[0] && pos1[1] == pos2[1]){
                            placed = false;
                            pos2 = new int[2]{0, 0};
                            drawer->drawSentence("Punto iniziale uguale a punto finale. Posizione non valida!");
                        }
                    }
                }
                
                // Se la nave è stata piazzata con successo disegna le navi sulla griglia
                if(placed){

                    // NON TOCCARE
                    // ships.push_back(new Ship(pos1, pos2, size, grid));
                    // new Ship(new int[2]{0, 0}, new int[2]{0, 0}, 0, grid);
                    // Disegna nave
                    
                    // DA MIGLIORARE CON: if(pos1[0] == pos2[0]) ecc.
                    int dx = pos2[0] - pos1[0];
                    int dy = pos2[1] - pos1[1];

                    if(dx == 0){
                        if(dy > 0){
                            for (int y = 0; y < dy + 1; y++){
                                grid->setValue((pos1[0] - 31)/2, pos1[1] + y - 5, 1);
                            }
                        }
                        else {
                            for (int y = 0; y < -dy + 1; y++){
                                grid->setValue((pos1[0] - 31)/2, pos1[1] - y - 5, 1);
                            }
                        }
                        
                    } else if(dy == 0){
                        if(dx > 0){
                            for (int x = 0; x < dx; x++){
                                grid->setValue(((pos1[0] + x - 31))/2, pos1[1] - 5, 1);
                            }
                        }
                        else {
                            for (int x = 0; x < -dx+1; x++){
                                grid->setValue(((pos1[0] - x - 31))/2, pos1[1] - 5, 1);
                            }
                        }
                    }

                    // Se tutto è stato eseguito si può uscire dal loop principale
                    done = false;
                }
            } else {
                // Else eseguito se la lunghezza della nave è 1
                grid->setValue(((pos1[0] - 31))/2, pos1[1] - 5, 1);
                pos2 = pos1;
                //ships.push_back(new Ship(pos1, pos1, size, grid)); NON TOCCARE
                done = false;
            }
        };
    }

    // Restituzione della posizione finale
    return pos2;
}

