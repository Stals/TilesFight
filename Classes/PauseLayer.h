#pragma once

#include "Constants.h"

class PauseLayer : public CCLayer{
public:
	PauseLayer();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    CCMenu* menu = NULL;
    
    CCMenuItemSprite* button1;
    CCMenuItemSprite* button2;
    CCMenuItemSprite* button3;
    
private:
	void setupBackground();
    void setupButtons();
    
    void resumeChosen(CCObject* pSender);
    void restartChosen(CCObject* pSender);
	void menuChosen(CCObject* pSender);
};