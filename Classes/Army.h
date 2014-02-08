#pragma once

#include "Point.h"
#include "Hexagon.h"

class Army : cocos2d::CCObject{
public:
    Army(Hexagon* hex, int troopsCount, Hexagon* destination);
    ~Army();
    
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
