#pragma once

#include "Constants.h"

class Hexagon : public CCSprite, public cocos2d::CCTargetedTouchDelegate{
public:
	Hexagon();
	
private:
	virtual void onEnter();
    virtual void onExit();
	
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

    void registerWithTouchDispatcher();

    bool containsTouchLocation(cocos2d::CCTouch *touch);
    cocos2d::CCRect rect();
};
