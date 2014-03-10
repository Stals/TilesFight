#pragma once

#include "Constants.h"

class Hexagon;
class Player;

class ColorPicker : public CCLayer{
public:
    ColorPicker();
    virtual ~ColorPicker();
    
    void pickAtIndex(size_t index);
    
private:
    void setupHexagons();
    void setupColors();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    std::vector<ccColor3B> colors;
    std::vector<Hexagon*> hexagons;
    
    Player* owner;
};
