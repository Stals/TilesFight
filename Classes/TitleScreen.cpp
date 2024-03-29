#include "TitleScreen.h"
#include "GameLayer.h"
#include "Game.h"
#include "ButtonFactory.h"
#include "MusicPlayer.h"
#include "ExpandingLayer.h"
#include "ColorPicker.h"

#include "VsAIScreen.h"
#include "VsHumanScreen.h"
#include "TBAScreen.h"
#include "SettingsScreen.h"
#include "CreditsScreen.h"
#include "TutorialScreen.h"
#include "GameCenter.h"

TitleScreen::~TitleScreen()
{
}

CCScene* TitleScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScreen *layer = TitleScreen::create();
    
    // add layer as a child to scene
    scene->addChild(layer, 0, 1337);
    
    // return the scene
    return scene;
}

bool TitleScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	setupBackground();
	setupButtons();
    setupClippingSprite();
	setTouchEnabled(true);
    
    MusicPlayer::playMenuMusic();
	return true;
}

void TitleScreen::setupBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCSprite* bgSprite = CCSprite::create(IMG("loader.png"));
    bgSprite->setScale(Game::current().artScale());
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(bgSprite, zBackground);
}

void TitleScreen::setupButtons()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // row 1
    Button* buttonLeft = NULL;
    Button* buttonRight = NULL;
    
    buttonLeft = ButtonFactory::button(IMG("ai.png"), "QUICK\nBATTLE", ICON_RIGHT, new Handler(this, callfuncD_selector(TitleScreen::vsAIChosen)));
    buttonRight = ButtonFactory::button(IMG("human.png"), "HOT SEAT", ICON_LEFT, new Handler(this, callfuncD_selector(TitleScreen::vsHumanChosen)));
    
    buttonLeft->setPosition(ccp(winSize.width/2 - 340, winSize.height/2 + 60 + 3));
    buttonRight->setPosition(ccp(winSize.width/2 + 340, winSize.height/2 + 60 + 3));
    
    this->addChild(buttonLeft);
    this->addChild(buttonRight);
        
        
        
    // row 2
    buttonLeft = ButtonFactory::button(IMG("tutorial.png"), "TUTORIAL", ICON_RIGHT, new Handler(this, callfuncD_selector(TitleScreen::tutorialChosen)));
    buttonRight = ButtonFactory::button(IMG("gc.png"), "GAME\nCENTER", ICON_LEFT, new Handler(this, callfuncD_selector(TitleScreen::gamecenterChosen)));
    
    buttonLeft->setPosition(ccp(winSize.width/2 - 290, winSize.height/2 - 40 + 3));
    buttonRight->setPosition(ccp(winSize.width/2 + 290, winSize.height/2 - 40 + 3));
    
    this->addChild(buttonLeft);
    this->addChild(buttonRight);
        
    // row 3
    buttonLeft = ButtonFactory::button(IMG("settings.png"), "SETTINGS", ICON_RIGHT, new Handler(this, callfuncD_selector(TitleScreen::settingsChosen)));
    buttonRight = ButtonFactory::button(IMG("credits.png"), "CREDITS", ICON_LEFT, new Handler(this, callfuncD_selector(TitleScreen::creditsChosen)));

    buttonLeft->setPosition(ccp(winSize.width/2 - 240, winSize.height/2 - 140 + 3));
    buttonRight->setPosition(ccp(winSize.width/2 + 240, winSize.height/2 - 140 + 3));
    
    this->addChild(buttonLeft);
    this->addChild(buttonRight);
}

void TitleScreen::setupClippingSprite()
{
    expandingLayer = new ExpandingLayer;
    expandingLayer->setToggleHandler(new Handler(this, callfuncD_selector(TitleScreen::onCollapsed)));
    this->addChild(expandingLayer, zCippingSprite);
}

void TitleScreen::vsAIChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new VsAIScreen);
    expandingLayer->expand();
    setButtonsEnabled(false);
}

void TitleScreen::vsHumanChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new VsHumanScreen);
    expandingLayer->expand();
    setButtonsEnabled(false);
}

void TitleScreen::tutorialChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new TutorialScreen);
    expandingLayer->expand();
    setButtonsEnabled(false);
}

void TitleScreen::gamecenterChosen(CCObject* pSender)
{
    if(!GameCenter::showAchievements()){
        // this should not login if already loged in
        GameCenter::login();
    }
}

void TitleScreen::settingsChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new SettingsScreen);
    expandingLayer->expand();
    setButtonsEnabled(false);
}

void TitleScreen::creditsChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new CreditsScreen);
    expandingLayer->expand();
    setButtonsEnabled(false);
}

void TitleScreen::setButtonsEnabled(bool enabled)
{
    CCArray* childred = this->getChildren();
    
    for(int i = 0; i < childred->count(); i++)
    {
        cocos2d::CCObject *child = childred->objectAtIndex(i);
        Button* b = dynamic_cast<Button*>(child);
        if(b != 0) {
            b->setEnabled(enabled);
        }
    }
}

void TitleScreen::onCollapsed(void* data)
{
    setButtonsEnabled(true);
}
