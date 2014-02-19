#include "PauseLayer.h"
#include "ButtonFactory.h"
#include "Game.h"
#include "TitleScreen.h"

PauseLayer::PauseLayer()
{
	CCLayer::init();
	setupBackground();
    setupButtons();
}



void PauseLayer::setupBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	// загружаем 1 пиксель и скейлим
    
    CCSprite* bg = CCSprite::create(IMG("pixel.png"));
    bg->setScaleX(winSize.width);
    bg->setScaleY(winSize.height);
    bg->setColor(ccBLACK);
    bg->setOpacity(127);
    
    addChild(bg);
    
    bg->setPosition(ccp(winSize.width/2, winSize.height/2));

}

void PauseLayer::setupButtons()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* buttonImage1 = NULL;
    CCSprite* buttonImage2 = NULL;
    CCSprite* buttonImage3 = NULL;
    
    CCMenuItemSprite* button1 = NULL;
    CCMenuItemSprite* button2 = NULL;
    CCMenuItemSprite* button3 = NULL;

    CCMenu* menu = NULL;
    
    buttonImage1 = ButtonFactory::mainMenuButtonSprite(IMG("tutorial.png"), "RESUME", ICON_RIGHT);
    buttonImage2 = ButtonFactory::mainMenuButtonSprite(IMG("tutorial.png"), "RESTART", ICON_LEFT);
    buttonImage3 = ButtonFactory::mainMenuButtonSprite(IMG("tutorial.png"), "MENU", ICON_RIGHT);

    
    button1 = CCMenuItemSprite::create(buttonImage1, buttonImage1, buttonImage1,
                                          this, menu_selector(PauseLayer::resumeChosen));
    button2 = CCMenuItemSprite::create(buttonImage2, buttonImage2, buttonImage2,
                                           this, menu_selector(PauseLayer::restartChosen));
    button3 = CCMenuItemSprite::create(buttonImage3, buttonImage3, buttonImage3,
                                       this, menu_selector(PauseLayer::menuChosen));
    
    menu = CCMenu::create(button1, button2, button3, NULL);
	menu->alignItemsVerticallyWithPadding(-25);
    this->addChild(menu, 2);
    
    menu->setPosition(ccp(winSize.width/2 + button1->getContentSize().width/4, (winSize.height/2) ));


}

bool PauseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	if(this->isVisible()){
		return true;
	}
	return false;
}

void PauseLayer::onEnter(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -250, true);
    CCLayer::onEnter();
}

void PauseLayer::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void PauseLayer::resumeChosen(CCObject* pSender)
{
    Game::current().resumeGame();
}

void PauseLayer::restartChosen(CCObject* pSender)
{
    // TODO with current game type and correct AI, colors. ect
    Game::current().starNewGame();
}

void PauseLayer::menuChosen(CCObject* pSender)
{
    CCScene *pScene = TitleScreen::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
