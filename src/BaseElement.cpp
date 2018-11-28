#include "headers/BaseElement.h"

BaseElement::BaseElement(int x, int y){
    x = x;
    y = y;
    value = 0;
}

int BaseElement::getX(){
    return x;
}

int BaseElement::getY(){
    return y;
}

int BaseElement::getValue(){
    return value;
}

void BaseElement::setValue(int value){
    value = value;
}