//
//  VsHumanScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "SettingsScreen.h"
#include "../ButtonFactory.h"

#include "../../lib/cocos/gui/Button.h"
#include "../User.h"

#define FONT_SIZE 24.f
#define BUTTON_PRIORITY -261
#define PADDING_Y 50
#define TEXT_PADDING 10


SettingsScreen::SettingsScreen()
{
    setupMusic();
    setupEffects();
}


void SettingsScreen::setupMusic()
{
    musicButton = new Button(0, 0,
                             new Handler(this, menu_selector(SettingsScreen::toggleMusic)),
                             BUTTON_PRIORITY);
    updateMusicButton();
    
    musicButton->setPositionY(PADDING_Y/2);
    addChild(musicButton);
}

void SettingsScreen::setupEffects()
{
    effectsButton = new Button(0, 0,
                             new Handler(this, menu_selector(SettingsScreen::toggleEffects)),
                             BUTTON_PRIORITY);
    
    updateEffectsButton();
    
    effectsButton->setPositionY(-PADDING_Y/2);
    addChild(effectsButton);
}

void SettingsScreen::updateMusicButton()
{
    CCSprite* on = soundState(IMG("music_on.png"), "MUSIC ON");
    CCSprite* off = soundState(IMG("music_off.png"), "MUSIC OFF");
    off->setPositionX(off->getPositionX() + 8.5f);

    if(User::current()->isMusicEnabled()){
        musicButton->setImages(on, off);
    }else{
        musicButton->setImages(off, on);
    }
}

void SettingsScreen::updateEffectsButton()
{
    CCSprite* on = soundState(IMG("effect_on.png"), "EFFECTS ON");
    CCSprite* off = soundState(IMG("effect_off.png"), "EFFECTS OFF");
    off->setPositionX(off->getPositionX() + 8.5f);
    
    if(User::current()->isEffectsEnabled()){
        effectsButton->setImages(on, off);
    }else{
        effectsButton->setImages(off, on);
    }
}

void SettingsScreen::toggleMusic(cocos2d::CCObject* pSender){
    User::current()->setMusicEnable(!User::current()->isMusicEnabled());
    updateMusicButton();
}

void SettingsScreen::toggleEffects(cocos2d::CCObject* pSender){
    User::current()->setEffectsEnable(!User::current()->isEffectsEnabled());
    updateEffectsButton();
}

CCSprite* SettingsScreen::soundState(const std::string& imgPath, const std::string& text)
{
    CCSprite* sprite = CCSprite::create();
    CCSprite* icon = CCSprite::create(imgPath.c_str());
    CCLabelTTF* label = CCLabelTTF::create(text.c_str(), default_font.c_str(), FONT_SIZE);
    
    icon->setPositionX(label->getPositionX() - label->getContentSize().width/2 - icon->getContentSize().width);
    
    sprite->addChild(label);
    sprite->addChild(icon);
    
    sprite->setContentSize(CCSizeMake(label->getContentSize().width + icon->getContentSize().width,
                                      label->getContentSize().height));
    
    sprite->setPositionX((label->getContentSize().width + icon->getContentSize().width)/2);
    sprite->setPositionY(label->getContentSize().height/2);
    
    
    return sprite;
}

