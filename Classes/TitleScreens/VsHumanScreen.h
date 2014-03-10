#pragma once

#include "EmptyScreen.h"

class ColorPicker;

class VsHumanScreen : public EmptyScreen{
public:
    VsHumanScreen();
    
private:
    void setupColorPickers();
    void setupLabels();
    void setupButton();
    
    ColorPicker* picker1;
    ColorPicker* picker2;
    
    void startGame(cocos2d::CCObject* pSender);
};