#include "headers/Ship.h"
#include "headers/BaseElement.h"

Ship::Ship(int x, int y, int size){
    x = x;
    y = y;
    size = size;
    children = new BaseElement*[size];
}

bool Ship::isDestroyed(){
    for(int i = 0; i < size; i++){
        if(children[i]->getValue==1){
            return false;
        } else {
            return true;
        }
    }
}

void Ship::addBaseElements(BaseElement* baseElement, int i){
    children[i] = baseElement;
}