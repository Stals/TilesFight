//
//  VsHumanScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "VsHumanScreen.h"
#include "../ButtonFactory.h"
#include "Constants.h"
#include "../Game.h"
#include "../User.h"

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
    picker1 = new ColorPicker(0);
    picker2 = new ColorPicker(1);
    
    this->addChild(picker1);
    this->addChild(picker2);
    
    picker1->setPositionX(-this->getContentSize().width/4);
    picker2->setPositionX(this->getContentSize().width/4);
    
    picker1->pickAtIndex(User::current()->getVSHumanColor1());
    picker2->pickAtIndex(User::current()->getVSHumanColor2());
    
    picker1->addOther(picker2);
    picker2->addOther(picker1);
    
    picker1->setDelegate(this);
    picker2->setDelegate(this);
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
    Button* button = ButtonFactory::button(BUTTON_TEXT, new Handler(this, callfuncD_selector(VsHumanScreen::startGame)), -261);
    
    this->addChild(button);
}

void VsHumanScreen::startGame(CCObject* pSender)
{
    Player* player1 = new Player("PLAYER 1", picker1->getSelectedColor());
	Player* player2 = new Player("PLAYER 2", picker2->getSelectedColor());
    Game::current().starNewGame(player1, player2);
}

void VsHumanScreen::onChangedColor(ColorPicker* picker, int index)
{
    if(picker->getID() == 0){
        User::current()->setVSHumanColor1(index);
        
    }else{
        User::current()->setVSHumanColor2(index);
    }
}

float VsHumanScreen::getHeight()
{
    return EmptyScreen::getHeight() + 100;
}