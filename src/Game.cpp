// Inclusione degli header
#include "headers/Game.h"

// Including external lib
#include "ShipPlacer.cpp"

// Referenza all' std:: per evitare di doverlo riscrivere ongi
// volta
using std::to_string;

// Assegnazione del drawer
Drawer* Game::drawer = Drawer::getInstance();

// Creazione di array di griglie, una per piazzare le navi
// ed una per tenere memoria dell'input
Grid* Game::player1 = new Grid[2]{Grid(), Grid()};
Grid* Game::player2 = new Grid[2]{Grid(), Grid()};

// Vettori per tenere memoria della navi create
vector<Ship*> Game::ships1;
vector<Ship*> Game::ships2;


void Game::startingScreen(){
    // Operazioni iniziali
    player1[1].clean(-1);
    player2[1].clean(-1);

    // Pulitura della console, visualizzazione del titolo e di
    // una frase
    drawer->clearConsole();
    drawer->drawTitle("BATTAGLIA NAVALE TCF 2018");
    drawer->drawRules();
    drawer->drawSentence("Premi un tasto per continuare...");

    // Il gioco viene messo in pausa fino a che un tasto non è premuto
    drawer->pause();
    placingScreen();
}

void Game::placingScreen(){
    // Una schermata che indicha al giocatore 2 di girarsi
    drawer->clearConsole();   
    drawer->drawSentence(4,5,"GIOCATORE N.1, il GIOCATORE N.2 si è girato?");
    drawer->drawSentence("Se sì, premi un tasto per continuare...");
    drawer->pause();
    drawer->drawSentence(4,5,"GIOCATORE N.1, sei sicuro?");
    drawer->drawSentence("Se sì, premi un tasto per continuare...");
    drawer->pause();

    // Piazzamento delle navi del giocatore 1, dopo una pulizia della console
    drawer->clearConsole();
    drawer->drawTitle("PIAZZAMENTO NAVI - GIOCATORE N.1");
    ShipPlacer* P1 = new ShipPlacer(player1[0], ships1);

    // Una schermata che indicha al giocatore 1 di girarsi
    drawer->clearConsole();   
    drawer->drawSentence(4,5,"GIOCATORE N.2, il GIOCATORE N.1 si è girato?");
    drawer->drawSentence("Se sì, premi un tasto per continuare...");
    drawer->pause();
    drawer->drawSentence(4,5,"GIOCATORE N.2, sei sicuro?");
    drawer->drawSentence("Se sì, premi un tasto per continuare...");
    drawer->pause();

    // Piazzamento delle navi del giocatore 2, dopo una pulizia della
    // console
    drawer->clearConsole();
    drawer->drawTitle("PIAZZAMENTO NAVI - GIOCATORE N.2");
    ShipPlacer* P2 = new ShipPlacer(player2[0], ships2);  

    // Una schermata che informa che la fase di piazzamento si è conclusa e si passerà al gioco
    drawer->clearConsole();
    drawer->drawSentence(4,5,"La fase di posizionamento è finita con successo!!!");
    drawer->drawSentence("Per cominciare a giocare premi un tasto qualsiasi...");
    drawer->pause();
    playingScreen();
}

void Game::playingScreen(){
    // Pulizia della console
    drawer->clearConsole();

    // Contatore del turno
    int turn = 0;

    // Ciclo ripetuto fino a che non è verificata la condizione di perdita
    while(!lostCondition()){
        // Pulitura schermo
        drawer->clearConsole();

        // Disegno del titolo
        drawer->drawTitle("TURNO DEL GIOCATORE N." + to_string(turn%2+1));
        
        // Disegno della griglia
        if(turn%2 == 0){
            drawer->drawGrid(&player1[1]);
        } else {
            drawer->drawGrid(&player2[1]);
        }

        // Ottenere posizione colpita
        bool enter = false;
        int * pos = new int[2]{31, 5};
        while(!enter){
            pos = drawer->moveCursor(enter);
        }

        pos[0] = (pos[0] - 32)/2;
        pos[1] = pos[1] - 5;

        // Update della griglia
        if(turn%2 == 0){
            int value = player1[0].getValue(pos[0], pos[1]);
            player1[1].setValue(pos[0], pos[1], value == 1 ? 2 : 0);
            drawer->drawGrid(&player1[1]);
            if(value == 1){
                for(int i = 0; i < ships1.size(); i++){
                    if(!(ships1[i]->isAlive())){
                        for(int k = 0; k < ships1[i]->getSize(); k++){
                            int* pos1 = ships1[i]->getElement(k);
                            player1[1].setValue(pos1[0], pos1[1], 3);
                        }
                    }
                }
            }
        } else {
            int value = player2[0].getValue(pos[0], pos[1]);
            player2[1].setValue(pos[0], pos[1], value == 1 ? 2 : 0);
            drawer->drawGrid(&player2[1]);
            if(value == 1){
                for(int i = 0; i < ships2.size(); i++){
                    if(!(ships2[i]->isAlive())){
                        for(int k = 0; k < ships2[i]->getSize(); k++){
                            int* pos1 = ships2[i]->getElement(k);
                            player2[1].setValue(pos1[0], pos1[1], 3);
                        }
                    }
                }
            }
        }
        
        // NON FUNZIONA: Una frase che indica se è stata colpita una nave o dell'acqua
        if(turn%2 == 0){
            int value = player1[1].getValue(pos[0], pos[1]);
            //Debugger per vedere cosa c'è nella griglia
            //drawer->drawSentence(1,1,to_string(value));
            if(value == 2 ){
                drawer->drawSentence(4,19,"Hai colpito una nave!");
            }
            if(value == 3){
                drawer->drawSentence(4,19,"Hai affondato una nave!");
            }
            if(value == 0){
                drawer->drawSentence(4,19,"Hai bombardato dell'innocua acqua...");
            }
        }
        else{
            int value = player2[1].getValue(pos[0], pos[1]);
            //Debugger per vedere cosa c'è nella griglia
            //drawer->drawSentence(1,1,to_string(value));
            if(value == 2 ){
                drawer->drawSentence(4,19,"Hai colpito una nave!");
            }
            if(value == 3){
                drawer->drawSentence(4,19,"Hai affondato una nave!");
            }
            if(value == 0){
                drawer->drawSentence(4,19,"Hai bombardato dell'innocua acqua...");
            }
        }

        // Il giocatore viene informato che si è concluso il turno
        drawer->drawSentence("Il GIOCATORE " + to_string(turn%2+1) + " ha concluso il suo turno.");
        drawer->drawSentence(4, 22, "Premere un tasto per continuare...");
        drawer->pause();

        // Incremento del turno
        turn++;
    }   

    
}

bool Game::lostCondition(){
   /* bool condA = true;
    bool condB = true;
    for(int i = 0; i < ships1.size(); i++){
        if(ships1[i]->isAlive()){
            condA = false;
        }
    }
    for(int i = 0; i < ships2.size(); i++){
        if(ships2[i]->isAlive()){
            condB = false;
        }
    }

    return !(condA == condB);*/ // In un mondo ideale questo codice funzionerebbe... ma sono una capra e quindi no!
    bool condA = true;
    bool condB = true;
    bool c = false;

    for (int y = 0; y < 10; y++){
        for(int x = 0; x < 10; x++){
            if(player1[0].getValue(x, y) == 1 && player1[1].getValue(x, y) == -1){
                condA = false;
                break;
            }
        }
    }

    for (int y = 0; y < 10; y++){
        for(int x = 0; x < 10; x++){
            if(player2[0].getValue(x, y) == 1 && player2[1].getValue(x, y) == -1){
                condB = false;
                break;
            }
        }
    }

    if((condA == false && condB == true) || (condA == true && condB == false) || (condA == true && condB == true)){
        c = true;
    }

    //Dice che il gioco è finito
    if(c==true){
        drawer->clearConsole();
        drawer->drawSentence(4, 10, "Il gioco è finito, complimenti hai VINTO!!");
        drawer->drawSentence(4, 11, "Premere un tasto per chiudere il gioco...");
        drawer->pause();
    }
    return c;
}