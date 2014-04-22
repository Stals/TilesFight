#pragma once

#include "EmptyScreen.h"
#include "../ColorPicker.h"
#include "../Difficulty.h"

class AbstractAI;
class VsAIScreen : public EmptyScreen, public ColorPickerDelegate{
public:
    VsAIScreen();

    virtual void onChangedColor(ColorPicker* picker, int index);
    
    virtual float getHeight();
    
private:
    void setupColorPicker();
    void setupLabels();
    void setupButton();
    void setupEnemies();
    
    cocos2d::CCSprite* enemiesSprite();
    
    ColorPicker* picker;
    
    void startGame(cocos2d::CCObject* pSender);
    void onEnemySelected(void* data);
    
    AbstractAI* getAIForDifficulty(Difficulty::Type difficulty, Player* computer);
    ccColor3B getAIColor(Difficulty::Type difficulty, ccColor3B playerColor);
};