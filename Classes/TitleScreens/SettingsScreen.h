#pragma once

#include "EmptyScreen.h"
#include "Constants.h"


class Button;
class SettingsScreen : public EmptyScreen{
public:
    SettingsScreen();
    
private:
    Button* musicButton;
    Button* effectsButton;
    CCLabelTTF* musicLabel;
    CCLabelTTF* effectsLabel;
    
    void setupMusic();
    void setupEffects();
    
    void updateMusicButton();
    void updateEffectsButton();
    
    void toggleMusic(cocos2d::CCObject* pSender);
    void toggleEffects(cocos2d::CCObject* pSender);
    
    CCSprite* soundState(const std::string& imgPath, const std::string& text);
};