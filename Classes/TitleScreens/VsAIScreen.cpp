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
#define PADDING 10.f
#define BUTTON_TEXT "GO!"

#define BUTTON_PRIORITY -261

const char* titles[] = {"LIEUTENANT", "COMMANDER", "CAPTAIN", "ADMIRAL", "FLEET ADMIRAL"};
const char* names[] = {"GAIUS", "SHEPARD", "ALEXANDER", "HEX", "ENDER"};


bool operator==(const ccColor3B& color1, const ccColor3B& color2){
    return (color1.r == color2.r) &&
    (color1.g == color2.g) &&
    (color1.b == color2.b);
}

VsAIScreen::VsAIScreen()
{
    setupColorPicker();
    setupLabels();
    //setupButton();
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
    CCLabelTTF* label1 = CCLabelTTF::create("CHOOSE COLOR", default_font.c_str(), FONT_SIZE);
    CCLabelTTF* label2 = CCLabelTTF::create("CHOOSE DIFFICULTY", default_font.c_str(), FONT_SIZE);
    
    this->addChild(label1);
    this->addChild(label2);
    
    label1->setPosition(ccp(-this->getContentSize().width/4,
                           picker->getContentSize().height/2 + PADDING));
    
    label2->setPosition(ccp(this->getContentSize().width/4,
                            picker->getContentSize().height/2 + PADDING));
}

void VsAIScreen::setupButton()
{
    Button* button = ButtonFactory::button(BUTTON_TEXT, new Handler(this, callfuncD_selector(VsAIScreen::startGame)), BUTTON_PRIORITY);
    
    this->addChild(button);
}

void VsAIScreen::startGame(CCObject* pSender)
{
   /* Player* player = new Player("PLAYER", picker->getSelectedColor());
	Player* computer = new Player("COMMANDER", hexLightBlue); // TODO use AI name instead of just AI
    computer->setAI(new ExpansionAI(computer));
    
    Game::current().starNewGame(player, computer);*/
}

cocos2d::CCSprite* VsAIScreen::enemiesSprite()
{
    CCSprite* sprite = CCSprite::create();
    
    // create array here because else it crashes om compiling shaders for some odd reason
    AIButton* enemies[] = {
        new AIButton(titles[0], names[0], Difficulty::Easy, new Handler(this, callfuncD_selector(VsAIScreen::onEnemySelected), (void*)Difficulty::Easy), BUTTON_PRIORITY),
        new AIButton(titles[1], names[1], Difficulty::Normal, new Handler(this, callfuncD_selector(VsAIScreen::onEnemySelected), (void*)Difficulty::Normal), BUTTON_PRIORITY),
        new AIButton(titles[2], names[2], Difficulty::Hard, new Handler(this, callfuncD_selector(VsAIScreen::onEnemySelected), (void*)Difficulty::Hard), BUTTON_PRIORITY),
        new AIButton(titles[3], names[3], Difficulty::VeryHard, new Handler(this, callfuncD_selector(VsAIScreen::onEnemySelected), (void*)Difficulty::VeryHard), BUTTON_PRIORITY),
        new AIButton(titles[4], names[4], Difficulty::Impossible, new Handler(this, callfuncD_selector(VsAIScreen::onEnemySelected), (void*)Difficulty::Impossible), BUTTON_PRIORITY)
    };
    
    sprite->addChild(enemies[0]);
    sprite->addChild(enemies[1]);
    sprite->addChild(enemies[2]);
    sprite->addChild(enemies[3]);
    sprite->addChild(enemies[4]);
    
    enemies[0]->setPositionY(50);
    enemies[1]->setPositionY(50);
    
    enemies[2]->setPositionY(-30);
    enemies[3]->setPositionY(-30);

    enemies[4]->setPositionY(-110);
    
    
    enemies[0]->setPositionX(180);
    enemies[2]->setPositionX(180);
    
    enemies[1]->setPositionX(360);
    enemies[3]->setPositionX(360);
    
    enemies[4]->setPositionX(this->getContentSize().width/4);
    
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

float VsAIScreen::getHeight()
{
    return EmptyScreen::getHeight();
}

void VsAIScreen::onEnemySelected(void *data)
{
    Difficulty::Type selectedDifficulty = (Difficulty::Type)((int)data);

    Player* player = new Player("PLAYER", picker->getSelectedColor());
	Player* computer = new Player(titles[selectedDifficulty], getAIColor(selectedDifficulty, player->getColor()));
    computer->setAI(getAIForDifficulty(selectedDifficulty, computer));
    
    Game::current().starNewGame(player, computer);
}

AbstractAI* VsAIScreen::getAIForDifficulty(Difficulty::Type difficulty, Player* computer)
{
    return new ExpansionAI(computer);
}

ccColor3B VsAIScreen::getAIColor(Difficulty::Type difficulty, ccColor3B playerColor)
{
    ccColor3B enemyColor = Difficulty::getDifficultyColor(difficulty);
    
    if(enemyColor == playerColor){
        
        if(!(playerColor == hexOrange)){
            enemyColor = hexOrange;
        }else{
            enemyColor = hexLightBlue;
        }
    }
    
    return enemyColor;
}

