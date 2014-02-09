#pragma once

#include "Point.h"
#include "Hexagon.h"

class Army : cocos2d::CCObject{
public:
    Army(Hexagon* hex, int troopsCount, Hexagon* destination, bool selected = false);
    ~Army();
    
    Hexagon* getDestination();
    
    Hexagon* getCurrentHex();
    void setCurrentHex(Hexagon* hex);
    
    int getTroopsCount();
    void removeTroops(int count);
    
    void move(float dt);
    
    void setSelected(bool selected);
    bool isSelected();
    
private:
    Hexagon* currentHex;
    int troopsCount;
    Hexagon* destination;
    bool selected;
};
