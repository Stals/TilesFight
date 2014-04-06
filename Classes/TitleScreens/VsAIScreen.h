#pragma once

#include "EmptyScreen.h"
#include "../ColorPicker.h"


class VsAIScreen : public EmptyScreen, public ColorPickerDelegate{
public:
    VsAIScreen();

    virtual void onChangedColor(ColorPicker* picker, int index);
private:
    void setupColorPicker();
    void setupLabels();
    void setupButton();
    void setupEnemies();
    
    cocos2d::CCSprite* enemiesSprite();
    
    ColorPicker* picker;
    
    void startGame(cocos2d::CCObject* pSender);
};