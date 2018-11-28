#ifndef BASEELEMENT_H
#define BASEELEMENT_H

class BaseElement{

    private:
        // Position
        int x;
        int y;

        // Value
        int value;

    public:
        // BaseElement constructor
        BaseElement(int, int);

        // X, Y and value getters
        int getX();
        int getY();
        int getValue();

        // Setter for the elment value
        void setValue(int);
};

#endif