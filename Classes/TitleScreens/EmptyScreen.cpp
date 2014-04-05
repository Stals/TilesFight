//
//  EmptyScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "EmptyScreen.h"
#include "Constants.h"

#define BG_HEIGHT 300

using namespace cocos2d;

EmptyScreen::EmptyScreen(){
    
    CCLayer::init();
    this->autorelease();
    this->setTouchEnabled(true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(CCSizeMake(winSize.width, BG_HEIGHT));
    
    CCSprite* bg1 = CCSprite::create(IMG("screensBG3.png"));
    CCSprite* bg2 = CCSprite::create(IMG("screensBG3.png"));
    CCSprite* bg3 = CCSprite::create(IMG("screensBG3.png"));

    bg1->setPositionX(-bg2->getContentSize().width);
    bg3->setPositionX(bg2->getContentSize().width);
    
    //bg->setScale(0.8);
    //bg->setOpacity(127);
    
    this->addChild(bg1);
    this->addChild(bg2);
    this->addChild(bg3);
}

float EmptyScreen::getHeight()
{
    return BG_HEIGHT;
}