//
//  VsHumanScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "VsHumanScreen.h"
#include "../ColorPicker.h"
#include "../ButtonFactory.h"
#include "Constants.h"
#include "../Game.h"

#define FONT_SIZE 24.f
#define PADDING -5.f
#define BUTTON_TEXT "GO!"

VsHumanScreen::VsHumanScreen()
{
    setupColorPickers();
    setupLabels();
    setupButton();
}

void VsHumanScreen::setupColorPickers()
{
    picker1 = new ColorPicker;
    picker2 = new ColorPicker;
    
    this->addChild(picker1);
    this->addChild(picker2);
    
    picker1->setPositionX(-this->getContentSize().width/4);
    picker2->setPositionX(this->getContentSize().width/4);
    
    picker1->pickAtIndex(0);
    picker2->pickAtIndex(1);
}

void VsHumanScreen::setupLabels()
{
    CCLabelTTF* label1 = CCLabelTTF::create("PLAYER 1", default_font.c_str(), FONT_SIZE);
    CCLabelTTF* label2 = CCLabelTTF::create("PLAYER 2", default_font.c_str(), FONT_SIZE);
   
    this->addChild(label1);
    this->addChild(label2);
    
    label1->setPosition(ccp(picker1->getPositionX(),
                            picker1->getPositionY() + picker1->getContentSize().height/2 + PADDING));
    
    label2->setPosition(ccp(picker2->getPositionX(),
                            picker2->getPositionY() + picker2->getContentSize().height/2 + PADDING));
    
}

void VsHumanScreen::setupButton()
{
    CCSprite* buttonImage = ButtonFactory::buttonSprite(BUTTON_TEXT);    
    CCMenuItemSprite* button = CCMenuItemSprite::create(buttonImage, buttonImage, buttonImage,
                                        this, menu_selector(VsHumanScreen::startGame));
    
    CCMenu* menu = CCMenu::createWithItem(button);
    this->addChild(menu);
    
    menu->setPosition(ccp((buttonImage->getContentSize().width * buttonImage->getScaleX()) / 2,
                          (buttonImage->getContentSize().height * buttonImage->getScaleY()) / 2));

}

void VsHumanScreen::startGame(CCObject* pSender)
{
    Game::current().starNewGame(Game::VS_HUMAN);
}
