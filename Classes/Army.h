#pragma once

#include "Point.h"
#include "Hexagon.h"

class Army : public cocos2d::CCSprite{
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
    
    void free();
    
private:
    Hexagon* currentHex;
    int troopsCount;
    Hexagon* destination;
    bool selected;
};
