#pragma once

#include "Point.h"
#include "Hexagon.h"

class Army{
public:
    Army(Hexagon* hex, int troopsCount, Hexagon* destination);

    Hexagon* getDestination();
    
    Hexagon* getCurrentHex();
    void setCurrentHex(Hexagon* hex);
    
    int getTroopsCount();
    void removeTroops(int count);
    
    void move(float dt);
    
private:
    Hexagon* currentHex;
    int troopsCount;
    Hexagon* destination;
};
