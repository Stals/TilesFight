#pragma once

#include "Point.h"
#include "Hexagon.h"

class Army{
public:
    Army(Hexagon* hex, int troopsCount, Point destination);
    Hexagon* getCurrentHex();
	int getTroopsCount();
    void setCurrentHex(Hexagon* hex);
    Point getDestination();
    
private:
    Hexagon* currentHex;
    int troopsCount;
    Point destination;
    
    void move(float dt);
};
