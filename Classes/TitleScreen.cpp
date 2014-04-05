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
    
    buttonLeft = ButtonFactory::button(IMG("ai.png"), "VS AI", ICON_RIGHT, new Handler(this, menu_selector(TitleScreen::vsAIChosen)));
    buttonRight = ButtonFactory::button(IMG("human.png"), "VS HUMAN", ICON_LEFT, new Handler(this, menu_selector(TitleScreen::vsHumanChosen)));
    
    buttonLeft->setPosition(ccp(winSize.width/2 - 340, winSize.height/2 + 60 + 3));
    buttonRight->setPosition(ccp(winSize.width/2 + 340, winSize.height/2 + 60 + 3));
    
    this->addChild(buttonLeft);
    this->addChild(buttonRight);
        
        
        
    // row 2
    buttonLeft = ButtonFactory::button(IMG("tutorial.png"), "TUTORIAL", ICON_RIGHT, new Handler(this, menu_selector(TitleScreen::tutorialChosen)));
    buttonRight = ButtonFactory::button(IMG("gc.png"), "GAME\nCENTER", ICON_LEFT, new Handler(this, menu_selector(TitleScreen::gamecenterChosen)));
    
    buttonLeft->setPosition(ccp(winSize.width/2 - 290, winSize.height/2 - 40 + 3));
    buttonRight->setPosition(ccp(winSize.width/2 + 290, winSize.height/2 - 40 + 3));
    
    this->addChild(buttonLeft);
    this->addChild(buttonRight);
        
    // row 3
    buttonLeft = ButtonFactory::button(IMG("settings.png"), "SETTINGS", ICON_RIGHT, new Handler(this, menu_selector(TitleScreen::settingsChosen)));
    buttonRight = ButtonFactory::button(IMG("credits.png"), "CREDITS", ICON_LEFT, new Handler(this, menu_selector(TitleScreen::creditsChosen)));

    buttonLeft->setPosition(ccp(winSize.width/2 - 240, winSize.height/2 - 140 + 3));
    buttonRight->setPosition(ccp(winSize.width/2 + 240, winSize.height/2 - 140 + 3));
    
    this->addChild(buttonLeft);
    this->addChild(buttonRight);
}

void TitleScreen::setupClippingSprite()
{
    expandingLayer = new ExpandingLayer;
    this->addChild(expandingLayer, zCippingSprite);
}

void TitleScreen::vsAIChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new VsAIScreen);
    expandingLayer->expand();
}

void TitleScreen::vsHumanChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new VsHumanScreen);
    expandingLayer->expand();
}

void TitleScreen::tutorialChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new TBAScreen);
    expandingLayer->expand();
}

void TitleScreen::gamecenterChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new TBAScreen);
    expandingLayer->expand();
}

void TitleScreen::settingsChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new SettingsScreen);
    expandingLayer->expand();
}

void TitleScreen::creditsChosen(CCObject* pSender)
{
    expandingLayer->setContainer(new TBAScreen);
    expandingLayer->expand();
}
