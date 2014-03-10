#pragma once

#include "cocos2d.h"
#include "clippingSprite.h"

class ExpandingLayer : public cocos2d::CCLayer{
public:
    ExpandingLayer();
    
    void expand();
    void collapse();
    
    // добавляется на background
    void setContainer(cocos2d::CCNode* container);
    
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
    
    void setupClippingSprite();
    
    virtual void update(float dt);
    
    void drawBorders();
    
    virtual void draw();
};