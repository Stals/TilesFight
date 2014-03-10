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
    
    CCSprite* bg = CCSprite::create(IMG("screensBG.jpg"));
    bg->setScale(0.8);
    bg->setOpacity(127);
    
    this->addChild(bg);
}

float EmptyScreen::getHeight()
{
    return BG_HEIGHT;
}