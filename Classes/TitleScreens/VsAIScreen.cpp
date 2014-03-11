//
//  VsAIScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "VsAIScreen.h"
#include "../ColorPicker.h"
#include "../ButtonFactory.h"
#include "Constants.h"
#include "../Game.h"

#define FONT_SIZE 24.f
#define PADDING -5.f
#define BUTTON_TEXT "GO!"


VsAIScreen::VsAIScreen()
{
    setupColorPicker();
    setupLabels();
    setupButton();
}

void VsAIScreen::setupColorPicker()
{
    picker = new ColorPicker;
    
    this->addChild(picker);
    
    picker->setPositionX(-this->getContentSize().width/4);
    
    picker->pickAtIndex(0);

}

void VsAIScreen::setupLabels()
{
    CCLabelTTF* label1 = CCLabelTTF::create("PLAYER", default_font.c_str(), FONT_SIZE);
    CCLabelTTF* label2 = CCLabelTTF::create("AI", default_font.c_str(), FONT_SIZE);
    
    this->addChild(label1);
    this->addChild(label2);
    
    label1->setPosition(ccp(-this->getContentSize().width/4,
                           picker->getContentSize().height/2 + PADDING));
    
    label2->setPosition(ccp(this->getContentSize().width/4,
                            picker->getContentSize().height/2 + PADDING));
}

void VsAIScreen::setupButton()
{
    Button* button = ButtonFactory::button(BUTTON_TEXT, new Handler(this, menu_selector(VsAIScreen::startGame)), -261);
    
    this->addChild(button);
}

void VsAIScreen::startGame(CCObject* pSender)
{
    Game::current().starNewGame(Game::VS_AI);
}