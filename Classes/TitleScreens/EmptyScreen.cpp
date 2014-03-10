//
//  EmptyScreen.cpp
//  HelloCpp
//
//  Created by Stanislav Korotaev on 3/10/14.
//
//

#include "EmptyScreen.h"
#define BG_HEIGHT 300

using namespace cocos2d;

EmptyScreen::EmptyScreen(){
    
    CCLayer::init();
    this->autorelease();
    this->setTouchEnabled(true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(CCSizeMake(winSize.width, BG_HEIGHT));
}

float EmptyScreen::getHeight()
{
    return BG_HEIGHT;
}