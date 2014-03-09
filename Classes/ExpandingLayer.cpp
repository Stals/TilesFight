#include "ExpandingLayer.h"

#include "Constants.h"

#define BG_HEIGHT 200

#define EXPAND_TIME 2.f
#define COLLAPSE_TIME EXPAND_TIME

#define PXL_PER_TICK 6.f

ExpandingLayer::ExpandingLayer(): currentState(Idle)
{
    CCLayer::init();
    this->autorelease();
    this->scheduleUpdate();
    
    setupClippingSprite();
}


void ExpandingLayer::setupClippingSprite()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    bg = CCSprite::create(IMG("pixel.png"));
    bg->setColor(ccc3(0, 0, 0));
    bg->setScaleX(winSize.width);
    bg->setScaleY(BG_HEIGHT);
    
    clippingSprite = new ClippingSprite;
    clippingSprite->setClippingRegion(CCRectMake(-winSize.width/2, 0, winSize.width, 0));
    clippingSprite->addChild(bg);
    this->addChild(clippingSprite);
    clippingSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
}

void ExpandingLayer::expand()
{
    currentState = Expanding;
}

void ExpandingLayer::collapse()
{
    currentState = Collapsing;
}

void ExpandingLayer::update(float dt)
{
    if(currentState == Idle) return;
    
    CCSize rect = clippingSprite->getContentSize();
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    if(currentState == Expanding){
        rect.height += PXL_PER_TICK;
        if(rect.height > BG_HEIGHT) rect.height = BG_HEIGHT;
        
        clippingSprite->setClippingRegion(CCRectMake(-winSize.width/2, -rect.height/2, winSize.width, rect.height));
        
        if(rect.height == BG_HEIGHT){
            currentState = Idle;
        }
        
    }else if (currentState == Collapsing){
        
        rect.height -= PXL_PER_TICK;
        if(rect.height < 0) rect.height = 0;
        
        clippingSprite->setClippingRegion(CCRectMake(-winSize.width/2, -rect.height/2, winSize.width, rect.height));
        
        if(currentState == 0){
            currentState = Idle;
        }
    }
}


