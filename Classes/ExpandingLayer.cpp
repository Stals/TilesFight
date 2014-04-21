#include "ExpandingLayer.h"

#include "Constants.h"

#include "EffectPlayer.h"

//#define BG_HEIGHT EmptyScreen::getHeight()

#define EXPAND_TIME 2.f
#define COLLAPSE_TIME EXPAND_TIME

#define PXL_PER_TICK (int)((container->getHeight() / 21.428f) + 0.5f);
#define LINE_WIDTH 6.f


ExpandingLayer::ExpandingLayer(): currentState(Idle), container(NULL), handler(0)
{
    CCLayer::init();
    this->autorelease();
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    
    setupClippingSprite();
}

ExpandingLayer::~ExpandingLayer()
{
    if(handler) delete handler;
}

void ExpandingLayer::setupClippingSprite()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    bg = CCSprite::create(IMG("pixel.png"));
    bg->setColor(ccc3(0, 0, 0));
    bg->setScaleX(winSize.width);
    bg->setScaleY(300 + 100);
    
    clippingSprite = new ClippingSprite;
    clippingSprite->setClippingRegion(CCRectMake(-winSize.width/2, 0, winSize.width, 0));
    clippingSprite->addChild(bg);
    this->addChild(clippingSprite);
    clippingSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
}

void ExpandingLayer::expand()
{
    currentState = Expanding;
    EffectPlayer::playerDoorEffect();
}

void ExpandingLayer::collapse()
{
    currentState = Collapsing;
    EffectPlayer::playerDoorEffect();
}

void ExpandingLayer::update(float dt)
{
    
    if(currentState == Idle) return;
    
    CCSize rect = clippingSprite->getContentSize();
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    if(currentState == Expanding){
        rect.height += PXL_PER_TICK;
        if(rect.height > container->getHeight()) rect.height = container->getHeight();
        
        clippingSprite->setClippingRegion(CCRectMake(-winSize.width/2, -rect.height/2, winSize.width, rect.height));
        
        if(rect.height == container->getHeight()){
            currentState = Idle;
        }
        
    }else if (currentState == Collapsing){
        
        rect.height -= PXL_PER_TICK;
        if(rect.height < 0) rect.height = 0;
        
        clippingSprite->setClippingRegion(CCRectMake(-winSize.width/2, -rect.height/2, winSize.width, rect.height));
        
        if(rect.height == 0){
            // call that its collapsed
            if(handler) handler->call();
            currentState = Idle;
            
            if(container){
                container->removeFromParentAndCleanup(true);
                container = NULL;
            }
        }
    }
}

void ExpandingLayer::setContainer(EmptyScreen* cont)
{
    if(container){
        container->removeFromParentAndCleanup(true);
        container = NULL;
    }
    
    this->container = cont;
    clippingSprite->addChild(container);
}

void ExpandingLayer::draw()
{
    drawBorders();
}

void ExpandingLayer::drawBorders()
{
    CCSize rect = clippingSprite->getContentSize();
    if(rect.height == 0) return;
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint start1  = ccp(0, (winSize.height/2) - (rect.height/2));
    CCPoint end1    = ccp(winSize.width, (winSize.height/2) - (rect.height/2));
    
    CCPoint start2 = start1;
    CCPoint end2 = end1;
    start2.y = (winSize.height/2) + (rect.height/2);
    end2.y = (winSize.height/2) + (rect.height/2);

    glLineWidth(LINE_WIDTH);
    cocos2d::ccDrawColor4B(255, 255, 255, 255);
    cocos2d::ccDrawLine(start1, end1);
    cocos2d::ccDrawLine(start2, end2);
}

bool ExpandingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCSize size = clippingSprite->getContentSize();
    CCRect rect =  CCRectMake(0, clippingSprite->getPositionY() - size.height/2, size.width, size.height);
    
    
    if(size.height == 0) return false;

    if(!rect.containsPoint( this->convertTouchToNodeSpace(pTouch))){
        collapse();
        return true;
    }
    
    return false;
}

void ExpandingLayer::onEnter(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -260, true);
    CCLayer::onEnter();
}
void ExpandingLayer::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void ExpandingLayer::setToggleHandler(Handler* handler)
{
    this->handler = handler;
}
