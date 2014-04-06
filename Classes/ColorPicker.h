#pragma once

#include "Constants.h"

class Hexagon;
class Player;

class ColorPicker;
class ColorPickerDelegate{
public:
    virtual void onChangedColor(ColorPicker* picker, int index) = 0;
};

class ColorPicker : public CCLayer{
public:
    ColorPicker(int id = 0);
    virtual ~ColorPicker();
    void setDelegate(ColorPickerDelegate* delegate);
    // returns picker id
    int getID();
    
    void pickAtIndex(size_t index);
    
    ccColor3B getSelectedColor();
    int getSelectedIndex();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void onEnter();
	virtual void onExit();
    
    void addOther(ColorPicker* picker);
    
private:
    void setupHexagons();
    void setupColors();
    
    void deselectAll();
    
    bool isSelectable(size_t index);
    
    int id;
    
    std::vector<ccColor3B> colors;
    std::vector<Hexagon*> hexagons;
    
    Player* owner;
    
    std::vector<ColorPicker*> otherPickers;
    ColorPickerDelegate* delegate;
};
