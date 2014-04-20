#pragma once

#include "cocos2d.h"
#include "clippingSprite.h"
#include "../lib/cocos/gui/Handler.h"

class ExpandingLayer : public cocos2d::CCLayer{
public:
    ExpandingLayer();
    virtual ~ExpandingLayer();
    
    void expand();
    void collapse();
    
    // добавляется на background
    void setContainer(cocos2d::CCNode* container);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void onEnter();
	virtual void onExit();
    
    void setToggleHandler(Handler* handler);
    
private:
    enum State{
        Expanding,
        Collapsing,
        Idle
    };
    State currentState;
    ClippingSprite* clippingSprite;
    cocos2d::CCSprite* bg;
    
    cocos2d::CCNode* container;
    
    Handler* handler;
    
    void setupClippingSprite();
    
    virtual void update(float dt);
    
    void drawBorders();
    
    virtual void draw();
};