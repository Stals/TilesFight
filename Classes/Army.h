#pragma once

#include "Point.h"
#include "Hexagon.h"

class Army{
public:
    Army(Hexagon* hex, int troopsCount, Point destination);

    Point getDestination();
    
    Hexagon* getCurrentHex();
    void setCurrentHex(Hexagon* hex);
    
    int getTroopsCount();
    void removeTroops(int count);
    
private:
    Hexagon* currentHex;
    int troopsCount;
    Point destination;
    
    void move(float dt);
};
