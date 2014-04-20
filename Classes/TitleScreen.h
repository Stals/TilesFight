#pragma once

#include "Constants.h"

class ExpandingLayer;

class TitleScreen : public CCLayer{
public:
    enum zOrder{
        zBackground,
        zButtons,
        zCippingSprite
    };
    
	~TitleScreen();
	virtual bool init();
	static cocos2d::CCScene* scene();
    
private:
    ExpandingLayer* expandingLayer;
    
	CREATE_FUNC(TitleScreen);
    
	void setupBackground();
	void setupButtons();
    void setupClippingSprite();
    
	void vsAIChosen(CCObject* pSender);
    void vsHumanChosen(CCObject* pSender);
	void tutorialChosen(CCObject* pSender);
	void gamecenterChosen(CCObject* pSender);
	void settingsChosen(CCObject* pSender);
	void creditsChosen(CCObject* pSender);

    void setButtonsEnabled(bool enabled);
    
    void onCollapsed(void* data);
};