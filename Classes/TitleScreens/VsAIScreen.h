#pragma once

#include "EmptyScreen.h"

class ColorPicker;

class VsAIScreen : public EmptyScreen{
public:
    VsAIScreen();

private:
    void setupColorPicker();
    void setupLabels();
    void setupButton();
    
    ColorPicker* picker;
    
    void startGame(cocos2d::CCObject* pSender);
};