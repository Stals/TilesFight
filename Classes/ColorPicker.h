#pragma once

#include "Constants.h"

class Hexagon;
class Player;

class ColorPicker : public CCLayer{
public:
    ColorPicker();
    virtual ~ColorPicker();
    
    void pickAtIndex(size_t index);
    
    ccColor3B getSelectedColor();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void onEnter();
	virtual void onExit();
    
private:
    void setupHexagons();
    void setupColors();
    
    void deselectAll();
    
    std::vector<ccColor3B> colors;
    std::vector<Hexagon*> hexagons;
    
    Player* owner;
};
