//
//  VsAIScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "VsAIScreen.h"
#include "../ButtonFactory.h"
#include "Constants.h"
#include "../Game.h"
#include "../ai/ExpansionAI.h"
#include "../AIButton.h"
#include "../User.h"

#define FONT_SIZE 24.f
#define PADDING -5.f
#define BUTTON_TEXT "GO!"

#define BUTTON_PRIORITY -261


VsAIScreen::VsAIScreen()
{
    setupColorPicker();
    setupLabels();
    setupButton();
    setupEnemies();
}

void VsAIScreen::setupColorPicker()
{
    picker = new ColorPicker;
    picker->setPositionX(-this->getContentSize().width/4);
    picker->pickAtIndex(User::current()->getVSAIColor());
    picker->setDelegate(this);
    this->addChild(picker);
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
    Button* button = ButtonFactory::button(BUTTON_TEXT, new Handler(this, menu_selector(VsAIScreen::startGame)), BUTTON_PRIORITY);
    
    //this->addChild(button);
}

void VsAIScreen::startGame(CCObject* pSender)
{
    Player* player = new Player("PLAYER", picker->getSelectedColor());
	Player* computer = new Player("AI", hexLightBlue); // TODO use AI name instead of just AI
    computer->setAI(new ExpansionAI(computer));
    
    Game::current().starNewGame(player, computer);
}

cocos2d::CCSprite* VsAIScreen::enemiesSprite()
{
    CCSprite* sprite = CCSprite::create();
    
    // create array here because else it crashes om compiling shaders for some odd reason
    AIButton* enemies[] = {
        new AIButton("LIEUTENANT", "GAIUS", Difficulty::Easy, 0, BUTTON_PRIORITY),
        new AIButton("COMMANDER", "SHEPARD", Difficulty::Normal, 0, BUTTON_PRIORITY),
        new AIButton("CAPTAIN", "ALEXANDER", Difficulty::Hard, 0, BUTTON_PRIORITY),
        new AIButton("ADMIRAL", "HEX", Difficulty::VeryHard, 0, BUTTON_PRIORITY),
        new AIButton("FLEET ADMIRAL", "ENDER", Difficulty::Impossible, 0, BUTTON_PRIORITY)
    };
    
    sprite->addChild(enemies[0]);
    sprite->addChild(enemies[1]);
    sprite->addChild(enemies[2]);
    sprite->addChild(enemies[3]);
    
    enemies[0]->setPositionY(50);
    enemies[2]->setPositionY(-50);
    
    enemies[1]->setPositionY(50);
    enemies[3]->setPositionY(-50);
    
    
    enemies[0]->setPositionX(170);
    enemies[2]->setPositionX(170);
    
    enemies[1]->setPositionX(370);
    enemies[3]->setPositionX(370);
    
    
    return sprite;
}


void VsAIScreen::setupEnemies()
{
    CCSprite* sprite = enemiesSprite();
    sprite->setPositionX(this->getContentSize().width/2);
    this->addChild(enemiesSprite());
}

void VsAIScreen::onChangedColor(ColorPicker* picker, int index)
{
    User::current()->setVSAIColor(index);
}