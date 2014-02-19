#pragma once

#include "Constants.h"

class PauseLayer : public CCLayer{
public:
	PauseLayer();
    
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
	virtual void onEnter();
	virtual void onExit();
    
private:
	void setupBackground();
    void setupButtons();
    
    void resumeChosen(CCObject* pSender);
    void restartChosen(CCObject* pSender);
	void menuChosen(CCObject* pSender);
};