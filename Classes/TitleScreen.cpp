#include "TitleScreen.h"
#include "GameLayer.h"
#include "Game.h"
#include "ButtonFactory.h"

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
	setTouchEnabled(true);
    
	return true;
}

void TitleScreen::setupBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCSprite* bgSprite = CCSprite::create(IMG("loader.png"));
    bgSprite->setScale(Game::current().artScale());
	bgSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(bgSprite);
}

void TitleScreen::setupButtons()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* buttonImageLeft = NULL;
    CCSprite* buttonImageRight = NULL;
    
    CCMenuItemSprite *buttonLeft = NULL;
    CCMenuItemSprite *buttonRight = NULL;
    
    CCMenu* menu = NULL;
    
    
    // 1 row
    buttonImageLeft = ButtonFactory::mainMenuButtonSprite(IMG("ai.png"), "VS AI", ICON_RIGHT);
    buttonImageRight = ButtonFactory::mainMenuButtonSprite(IMG("human.png"), "VS HUMAN", ICON_LEFT);

    buttonLeft = CCMenuItemSprite::create(buttonImageLeft, buttonImageLeft, buttonImageLeft,
                                          this, menu_selector(TitleScreen::vsAIChosen));
    buttonRight = CCMenuItemSprite::create(buttonImageRight, buttonImageRight, buttonImageRight,
                                           this, menu_selector(TitleScreen::vsHumanChosen));
    
    menu = CCMenu::create(buttonLeft, buttonRight, NULL);
	menu->alignItemsHorizontallyWithPadding(300);
    this->addChild(menu, 2);
    menu->setPosition(ccp(winSize.width/2 + buttonLeft->getContentSize().width/4, (winSize.height/2) + 100 - 3));

    
    
    // 2 row
    buttonImageLeft = ButtonFactory::mainMenuButtonSprite(IMG("tutorial.png"), "TUTORIAL", ICON_RIGHT);
    buttonImageRight = ButtonFactory::mainMenuButtonSprite(IMG("gc.png"), "GAME\nCENTER", ICON_LEFT);
    
    buttonLeft = CCMenuItemSprite::create(buttonImageLeft, buttonImageLeft, buttonImageLeft,
                                          this, menu_selector(TitleScreen::tutorialChosen));
    buttonRight = CCMenuItemSprite::create(buttonImageRight, buttonImageRight, buttonImageRight,
                                           this, menu_selector(TitleScreen::gamecenterChosen));
    
    menu = CCMenu::create(buttonLeft, buttonRight, NULL);
	menu->alignItemsHorizontallyWithPadding(200);
    this->addChild(menu, 2);
    menu->setPosition(ccp(winSize.width/2 + buttonLeft->getContentSize().width/4, (winSize.height/2) - 3));
    
    
    // 3 row
    
    buttonImageLeft = ButtonFactory::mainMenuButtonSprite(IMG("settings.png"), "SETTINGS", ICON_RIGHT);
    buttonImageRight = ButtonFactory::mainMenuButtonSprite(IMG("credits.png"), "CREDITS", ICON_LEFT);
    
    buttonLeft = CCMenuItemSprite::create(buttonImageLeft, buttonImageLeft, buttonImageLeft,
                                          this, menu_selector(TitleScreen::settingsChosen));
    buttonRight = CCMenuItemSprite::create(buttonImageRight, buttonImageRight, buttonImageRight,
                                           this, menu_selector(TitleScreen::creditsChosen));
    
    menu = CCMenu::create(buttonLeft, buttonRight, NULL);
	menu->alignItemsHorizontallyWithPadding(100);
    this->addChild(menu, 2);
    menu->setPosition(ccp(winSize.width/2 + buttonLeft->getContentSize().width/4, (winSize.height/2) - 100 - 3));
}

void TitleScreen::vsAIChosen(CCObject* pSender)
{
    Game::current().starNewGame(Game::VS_AI);
}

void TitleScreen::vsHumanChosen(CCObject* pSender)
{
    Game::current().starNewGame(Game::VS_HUMAN);
}

void TitleScreen::tutorialChosen(CCObject* pSender)
{
    
}

void TitleScreen::gamecenterChosen(CCObject* pSender)
{
    
}

void TitleScreen::settingsChosen(CCObject* pSender)
{
    
}

void TitleScreen::creditsChosen(CCObject* pSender)
{

}
