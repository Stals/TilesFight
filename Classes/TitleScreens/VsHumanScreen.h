#pragma once

#include "EmptyScreen.h"
#include "../ColorPicker.h"


class VsHumanScreen : public EmptyScreen, public ColorPickerDelegate{
public:
    VsHumanScreen();
    
    virtual void onChangedColor(ColorPicker* picker, int index);
    
    virtual float getHeight();
    
private:
    void setupColorPickers();
    void setupLabels();
    void setupButton();
    
    ColorPicker* picker1;
    ColorPicker* picker2;
    
    void startGame(cocos2d::CCObject* pSender);
};